#pragma once
#include"irc.hpp"
#include "clients.hpp"
#include "command.hpp"
#include <map>


struct SocketClient
{
    int            fd;
    socklen_t       addr_size;
    sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */
};

class serveur
{
    private:
    public:
    //constructeur
    serveur(char *port, char *password);
    ~serveur();
    
    //variable
        static std::map<int, clients*> mapClients;
        int indexmap;
        int port;
        std::string     NickName;
        std::string     UserName;
        static std::string     serv_password;
        std::string     ip;
        int           SocketServeur_fd;
        sockaddr_in   SocketServeur;
        int           SocketClient_fd;
        sockaddr_in  SocketClient;

        //fonction
        void    buildSocketServeur(void);
        void    buildSocketClient(void);
        void    initClientConnectionlvl1(void);
        int     pass_command(std::string Newpassword);
        void    command_detector(std::string cmd, std::string other, clients clients);
        void    parse_command(std::string command_line, clients clients);
        void    nick_command(std::string NewNick, clients clients);
        void    user_command(std::string NewUser, clients clients);
        void    addClientMap(serveur serveur);
};
