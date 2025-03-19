#include "../includes/irc.hpp"


void    ERR_PASSWDMISMATCH(clients *client)
{
    std::string msg;
    if (client->clientSentNick() == 1)
        msg =  ":ircserv 464 " + client->getNickname() + ":Password incorrect\r\n";
    else
        msg =  ":ircserv 464 * :Password incorrect\r\n";
    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
            std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
        }
}
void     ERR_ERRONEUSNICKNAME(clients *client)
{
    //peut etre le nick doit etre une * et pas le nick
    std::string msg;
    //if (client->clientSentNick() == 1)
    msg =  ":ircserv 432 " + client->getNickname() +  " * :Erroneus nickname\r\n";
    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
            std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
        }
}

void     ERR_NICKNAMEINUSE(clients *client)
{
    //peut etre le nick doit etre une * et pas le nick
    std::string msg;
    //if (client->clientSentNick() == 1)
    msg =  ":ircserv 433 * " + client->getNickname() + ":Nickname is already in use\r\n";
    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
            std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
        }
}
void     ERR_NONICKNAMEGIVEN(clients *client)
{
    std::string msg;
    if (client->clientSentNick() == 1)
        msg =  ":ircserv 431 " + client->getNickname() + ":No nickname given\r\n";
    else
        msg =  ":ircserv 431 * :No nickname given\r\n";
    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
            std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
        }
}

void    ERR_NEEDMOREPARAMS(clients *client, std::string command)
{
    std::string msg;
    if (client->clientSentNick() == 1)
        msg =  ":ircserv 461 " + client->getNickname() + command + ":Not enough parameters\r\n";
    else
        msg =  ":ircserv 461 * " + command + ":Not enough parameters\r\n";
    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
            std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
        }
}
void    ERR_ALREADYREGISTRED(clients *client)
{
    std::string msg;
    if (client->clientSentNick() == 1)
        msg =  ":ircserv 462 " + client->getNickname() + ":You may not reregister\r\n";
    else
        msg =  ":ircserv 462 * :You may not reregister\r\n";
    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
            std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
        }
}

void    ERR_BADCHANMASK(clients *client, const std::string &channelName)
{
    std::string msg = "ircserv 476 " + client->getNickname() + " " + channelName + " :Bad Channel Mask";
    
    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
    }
}

void    ERR_INVITEONLYCHAN(clients *client, const std::string &channelName)
{
    std::string msg;
    if (!client->getNickname().empty()) // Vérifie si le client a un pseudo défini
        msg = "ircserv 473 " + client->getNickname() + " " + channelName + " :Cannot join channel (+i)";
    else
        msg = "ircserv 473 * " + channelName + " :Cannot join channel (+i)";

    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
    }
}

void    ERR_BADCHANNELKEY(clients *client, const std::string &channelName)
{
    std::string msg;
    if (!client->getNickname().empty()) // Vérifie si le client a un pseudo défini
        msg = "ircserv 475 " + client->getNickname() + " " + channelName + " :Cannot join channel (+k)";
    else
        msg = "ircserv 475 * " + channelName + " :Cannot join channel (+k)";

    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
    }
}

void    ERR_CHANNELISFULL(clients *client, const std::string &channelName)
{
    std::string msg;
    if (!client->getNickname().empty()) // Vérifie si le client a un pseudo défini
        msg = "ircserv 471 " + client->getNickname() + " " + channelName + " :Cannot join channel (+l)";
    else
        msg = "ircserv 471 * " + channelName + " :Cannot join channel (+l)";

    ssize_t bytes_sent = send(client->getSocketname(), msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
        std::cerr << "Erreur lors de l'envoi du message au client." << std::endl;
    }
}