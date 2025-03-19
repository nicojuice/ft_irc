#include"../includes/irc.hpp"
#include "../includes/clients.hpp"
#include "../includes/exception.hpp"
#include "../includes/command.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <fcntl.h> 

std::string serveur::serv_password = "";
std::map<int, clients*> serveur::mapClients;

serveur::serveur(char *port, char *password)
{
    std::string port_string = port;
    this->indexmap = 0;
    int port_int = atoi(port);
    if (port_int <= 1024 || port_string.length() != 4 || isDigits(port_string) == false)
        throw Exception("Bad port");
    FILE* pipe;
    pipe = popen("hostname -i", "r");
    char buffer[258];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    result.erase(10);
    this->port = port_int;
    this->ip = result;
    serveur::serv_password = password;
    this->buildSocketServeur();
    std::cout << "Constructeur serveur\n";
    close(this->SocketServeur_fd);
}

serveur::~serveur()
{
    std::cout << "Destructeur serveur\n";
}

void serveur::buildSocketServeur(void)
{
    memset(&this->SocketServeur, 0, sizeof(this->SocketServeur));
    this->SocketServeur_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->SocketServeur_fd < 0) 
        throw Exception("Socket creation failed");
    if (fcntl(this->SocketServeur_fd, F_SETFL, O_NONBLOCK) == -1) 
        throw Exception("fcntl F_SETFL failed");
    this->SocketServeur.sin_family = AF_INET;
    this->SocketServeur.sin_addr.s_addr = INADDR_ANY;
    this->SocketServeur.sin_port = htons(this->port);
    int opt = 1;
    if (setsockopt(this->SocketServeur_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) 
        throw Exception("setsockopt failed");
    if (bind(this->SocketServeur_fd, (struct sockaddr*)&this->SocketServeur, sizeof(struct sockaddr_in)) < 0)
        throw Exception("Bind failed");
    if (listen(this->SocketServeur_fd, 10) < 0)
        throw Exception("Listen failed");
    buildSocketClient();
}



void serveur::buildSocketClient(void)
{
    fd_set readfds;
    int max_sd;
    int activity;

    while (true) 
    {
        FD_ZERO(&readfds);
        FD_SET(this->SocketServeur_fd, &readfds);
        max_sd = this->SocketServeur_fd;

        for (std::map<int, clients*>::iterator it = this->mapClients.begin(); it != this->mapClients.end(); ++it) 
        {
            int sd = it->first;
            if (sd > 0) {
                FD_SET(sd, &readfds);
                if (sd > max_sd) 
                    max_sd = sd;
            }
        }

        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0) && (errno != EINTR)) 
        {
            perror("select() failed");
            continue;
        }

        // Nouvelle connexion client détectée
        if (FD_ISSET(this->SocketServeur_fd, &readfds)) 
        {
            socklen_t addr_size = sizeof(this->SocketClient);
            int newSocketClient_fd = accept(this->SocketServeur_fd, (struct sockaddr*)&this->SocketClient, &addr_size);
            if (newSocketClient_fd < 0) 
            {
                perror("Accept failed");
                continue;
            }

            // Correction : assignation d'un pointeur
            clients* newClient = new clients(newSocketClient_fd, this);
            this->mapClients[newSocketClient_fd] = newClient;
            std::cout << "New client connected: " << newSocketClient_fd << std::endl;
        }

        // Gestion des clients existants
        for (std::map<int, clients*>::iterator it = this->mapClients.begin(); it != this->mapClients.end(); ) 
        {
            int sd = it->first;
            if (FD_ISSET(sd, &readfds)) 
            {
                char buffer[1024] = {0};
                int valread = recv(sd, buffer, sizeof(buffer), 0);
                std::string commandline(buffer);
                
                if (valread <= 0) 
                {
                    std::cout << "Client déconnecté : " << sd << std::endl;
                    close(sd);
                    delete it->second;
                    std::map<int, clients*>::iterator tmp = it;
                    ++it;
                    this->mapClients.erase(tmp);
                }
                else 
                {
                    std::cout << "Message du client " << sd << " : " << std::endl;
                    std::istringstream    input;
                    input.str(buffer);
                    for (std::string line; std::getline(input, line, '\n');)
                    {
                        //std::cout << "line is : " << line << std::endl;
                        command_list(line, it->second);
                        //this->exec_cmd(cmd, *(this->getClientByFd(fd)));
                    }
                    command_list(commandline, it->second);
                    if (commandline.find("QUIT") != std::string::npos) 
                    {
                        std::cout << "Client déconnecté : " << sd << std::endl;
                        close(sd);
                        delete it->second;
                        std::map<int, clients*>::iterator tmp = it;
                        ++it;
                        this->mapClients.erase(tmp);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
            else 
                ++it;
        }
    }
}
