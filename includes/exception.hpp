#pragma once
#include "irc.hpp"
#include <exception>
#include <string>
#include "clients.hpp"

// class Exception : public std::exception
// {
//     public:
//         explicit Exception(const std::string &message) : _message(message) {}
//         virtual ~Exception() throw();
//         virtual const char *what() const throw()
//         {
//             return _message.c_str();
//         }

//     private:
//         std::string _message;
// };


class Exception : public std::exception {
    public:
        explicit Exception(const std::string &message);
        virtual ~Exception() throw();
        virtual const char *what() const throw();

    private:
        std::string _message;
};

class ErrorCmd : public std::exception {
    public:
        explicit ErrorCmd(clients *client,const std::string &message, int errorNum);
        virtual ~ErrorCmd() throw();
        virtual const char *what() const throw();
        void    find_error(clients client, std::string message, int errorNum) const;

    private:
        clients *client;
        std::string _message;
        int     _errorNum;
};

