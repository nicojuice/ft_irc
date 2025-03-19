#include"../includes/irc.hpp"
#include "../includes/serveur.hpp"
//#include "../includes/exception.hpp"
//#include "error_message.cpp"
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <string>


void    ErrorCmd::find_error(clients client,std::string message, int errorNum) const
{
    std::cout << "errorNUm == " << errorNum << std::endl;
    if (errorNum == 461)
        ERR_NEEDMOREPARAMS(&client,message);
    if (errorNum == 462)
        ERR_ALREADYREGISTRED(&client);
    if (errorNum == 431)
        ERR_NONICKNAMEGIVEN(&client);
    if (errorNum == 432)
        ERR_ERRONEUSNICKNAME(&client);
    if (errorNum == 433)
        ERR_NICKNAMEINUSE(&client);
    if (errorNum == 464)
        ERR_PASSWDMISMATCH(&client);
}

Exception::Exception(const std::string &message) : _message(message) {}

Exception::~Exception() throw() {} // Implémentation manquante !

const char *Exception::what() const throw() {
    return _message.c_str();
}

ErrorCmd::ErrorCmd(clients *client,const std::string &message, int errorNum) : client(client), _message(message), _errorNum(errorNum)
{
    return ;
}

ErrorCmd::~ErrorCmd() throw() {} // Implémentation manquante !

const char *ErrorCmd::what() const throw() {
    find_error(*client,_message, _errorNum);
    return _message.c_str();
}


