#pragma once

#include <sys/socket.h>    // socket, bind, listen, accept, send, recv, setsockopt
#include <netinet/in.h>    // sockaddr_in, htons, htonl, ntohs, ntohl
#include <arpa/inet.h>     // inet_addr, inet_ntoa
#include <netdb.h>         // gethostbyname, getprotobyname, getaddrinfo, freeaddrinfo
#include <unistd.h>        // close, fstat, lseek
#include <signal.h>        // signal, sigaction
#include <fcntl.h>         // fcntl
#include <sys/select.h>    // select
#include <sys/types.h>     // fstat, general types like pid_t, size_t
#include <cstring>         // pour utiliser les fonctions de manipulation de chaînes C (au lieu de <string.h> en C++)
#include <cstdlib>
#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <sstream>
#include "irc.hpp"
#include "serveur.hpp"
#include "command.hpp"
#include "clients.hpp"
#include "exception.hpp"
#include "error_message.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BIG "\033[1m"
#define ITA "\033[3m"
#define FLASH "\033[5m"
#define LOW "\033[2m"
#define INVERT "\033[7m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"
#define BRIGHT_BLACK "\033[90m"
#define CLEAR_SCREEN "\033[2J"
#define MOVE_CURSOR_TOP_LEFT "\033[H"

#define BOLD        "\x1b[1m"
#define UNDERLINE    "\x1b[4m"
#define RESET        "\x1b[0m"

bool    isDigits(const std::string& str);
void    error_handler(int i);