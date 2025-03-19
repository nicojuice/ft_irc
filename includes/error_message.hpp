#pragma once
#include"irc.hpp"
#include "serveur.hpp"
#include "channel.hpp"
#include "clients.hpp"


void        ERR_ERRONEUSNICKNAME(clients *client);
void        ERR_PASSWDMISMATCH(clients *client);
void        ERR_NICKNAMEINUSE(clients *client);
void        ERR_NONICKNAMEGIVEN(clients *client);
void        ERR_NEEDMOREPARAMS(clients *client, std::string command);
void        ERR_ALREADYREGISTRED(clients *client);
void        ERR_BADCHANMASK(clients *client, const std::string &channelName);
void        ERR_INVITEONLYCHAN(clients *client, const std::string &channelName);
void        ERR_BADCHANNELKEY(clients *client, const std::string &channelName);
void        ERR_CHANNELISFULL(clients *client, const std::string &channelName);