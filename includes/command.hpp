#pragma once
#include"irc.hpp"
#include "serveur.hpp"
#include "clients.hpp"

void command_join(clients *client, std::string &arg);
void listClientInChannel(clients *client, Channel *channel);
std::vector<std::string> splitArgJ(const std::string str, char separator);
void   command_list(std::string command_line, clients *client);
void    pass_command(std::string Newpassword, clients *client);