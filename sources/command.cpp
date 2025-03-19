#include"../includes/irc.hpp"
#include "../includes/serveur.hpp"
#include "../includes/exception.hpp"
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>


#include <iostream>
#include <cstring>      // Pour strlen()
#include <sys/socket.h> // Pour send()
#include <unistd.h>     // Pour close()

void sendMessage(clients *client, int i)
{
    (void) i;
    std::string msg = "dfffffffff\r\n"; // IRC utilise "\r\n" comme fin de ligne
    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);

    if (bytes_sent == -1) {
        std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
    }
}


void    debug_command(clients *client)
{
    std::cout << "-- CLIENT DATA --\n";
    std::cout << "Socket -> " << client->getSocketname() <<std ::endl;
    std::cout << "Pass Status -> ";
    if (client->clientSentPass() == 0)
        std::cout << "⛔" << std::endl;
    else
        std::cout << "✅" << std::endl;
    std::cout << "NICK -> " << client->getNickname() << std::endl;
    std::cout << "USER -> " << client->getUsername() << std::endl;
    std::cout << "Register Status -> ";
    if (client->isRegistered() == 0)
        std::cout << "⛔" << std::endl;
    else
        std::cout << "✅" << std::endl;

}

void     pass_command(std::string Newpassword, clients *client)
{
    if (client-> clientSentPass() == 1)
        throw ErrorCmd(client,"PASS",462);
    if (Newpassword == "1511" || Newpassword.empty())
        throw ErrorCmd(client,"PASS",461);
    else if (Newpassword.compare(serveur::serv_password) == 1)
        client->clientPassStatus(1);
    else
        throw ErrorCmd(client,"PASS",464);
}

int AlreadyHaveThisNick(const std::string &NewNick, const std::map<int, clients*> &mapClients) 
{
    std::map<int, clients*>::const_iterator it = mapClients.begin();
    
    while (it != mapClients.end()) {
        if (it->second && it->second->getNickname() == NewNick) {
            return 1;
        }
        ++it;
    }
    return 2;
}

void    nick_command(std::string NewNick, clients *client)
{
    if (NewNick == "1511" || NewNick.empty())
        throw ErrorCmd(client,"NICK",431);
    if (NewNick.size() > 7)
        throw ErrorCmd(client,"NICK", 432);
    if (AlreadyHaveThisNick(NewNick,serveur::mapClients) == 1)
    {
        client->setNickname(NewNick);
        std::cout << RED << FLASH <<" ERROR \n" << RESET ;
        throw ErrorCmd(client,"NICK",433);
        return ;
    }
    client->setNickname(NewNick);
    client->clientNickStatus(1);
}

void    user_command(std::string NewUser, clients *client)
{
    std::istringstream iss(NewUser);
    std::string username, zero, etoile, realname;

    if (!(iss >> username >> zero >> etoile))
    {
        ERR_NEEDMOREPARAMS(client, "USER");
        std::cout << "Erreur: format USER incorrect1 (doit être 'USER <username> 0 * :<realname>')\n";
        return;
    }
    iss >> std::ws;
    std::getline(iss, realname);
    if (realname.empty() || realname[0] != ':')
    {
        ERR_NEEDMOREPARAMS(client, "USER");
        std::cout << "Erreur: format USER incorrect2 (doit être 'USER <username> 0 * :<realname>')\n";
        return;
    }
    if (zero != "0" || etoile != "*")
    {

        ERR_NEEDMOREPARAMS(client, "USER");
        std::cout << "Erreur: format USER incorrect3 (doit être 'USER <username> 0 * :<realname>')\n";
        return;
    }
    realname.erase(0, 1);
    client->setUsername(username);
    client->setRealname(realname);
    client->clientUserStatus(1);

    std::cout << "USER command acceptée : Username = " << username << ", Realname = " << realname << "\n";
}

std::string     get_good_commandline(std::string commandline)
{
    size_t i = commandline.find(" ");

    if(i != std::string::npos)
        commandline.resize(i);
    return commandline;
}

std::string     get_good_otherline(std::string commandline)
{
    size_t i = commandline.find(" ");

    if(i != std::string::npos)
    {
        commandline.erase(0, i + 1);
        i = commandline.find("\r\n");
    }
    else
        commandline = "1511";
    i = commandline.find("\n");
    if (i != std::string::npos)
        commandline.erase(i, i+1);
    return commandline;
}

std::string get_remove_line(std::string command_line) 
{
    std::string result;
    std::string::size_type i = 0;
    
    while (i < command_line.size()) {
        if (command_line[i] != '\n' && command_line[i] != '\r' && command_line[i] != '\f') {
            result += command_line[i];
        }
        ++i;
    }
    return result;
}

void    cap_ls_command(clients *client)
{
    std::string msg;
    msg =  "CAP END\r\n";
    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
            std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
        }
}
void   command_list(std::string command_line, clients *client)
{
    std::string cmd = get_good_commandline(command_line);
    std::string other = get_good_otherline(command_line);
    // std::cout << "command_line -->"<< command_line << "<-- command_line" << std::endl;
    if (cmd == "USER")
    {    
        std::cout << "CMD -->"<< cmd << "<-- CMD" << std::endl;
        std::cout << "other -->" << other << "<-- other" << std::endl;
    }
    try
    {
        if (cmd == "PASS")
        {
            pass_command(other, client);
            return ;
        }
        else if (cmd == "CAP")
            return ;
        else if (cmd == "NICK")
        {
            nick_command(other, client);
            return;
        }
        else if (cmd == "DEBUG")
        {
            debug_command(client);
        }
        else if (cmd == "USER")
        {
            user_command(other, client);
        }
        // else if (cmd == "JOIN")
        // {
        //     command_join(client,other);
        // }
    }
    catch(const std::exception& e)
    {
        std::cerr << RED <<"ERROR CMD -> " << RESET << e.what() << '\n';
        return ;
    }
}