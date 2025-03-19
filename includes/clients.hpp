#pragma once
#include"irc.hpp"
#include "serveur.hpp"
#include "channel.hpp"
#include <map>

class serveur;

class clients
{
    private:

        int _socket;

        std::string _nickname;
        std::string _username;
        std::string _realname;
        std::string _hostname;
        std::string _servername;
        
        std::set<Channel *> _chan;

        bool _registered;
        bool _clientSentPass;
        bool _clientSentNick;
        bool _clientSentUser;

        serveur *_serveur;
    
    public:
        clients(int socket, serveur *serveur);
        clients();
        friend std::ostream& operator<<(std::ostream& os, const clients& client) 
        {
            os << "Client FD: " << client._socket;
            return os;
        }
        //~clients();
        //void addClient(serveur serveur); //, const std::string &nick, const std::string &user);
        //void removeClient(int i);

        const std::string &getNickname() const;
        const std::string &getUsername() const;
        const std::string &getRealname() const;
        const std::string &getHostname() const;
        const std::string &getServername() const;
        const int &getSocketname() const;

        void setSocket(int socket);
        void setNickname(const std::string &nickname);
        void setUsername(const std::string &username);
        void setRealname(const std::string &realname);
        void setHostname(const std::string &hostname);
        void setServername(const std::string &servername);
        void setRegistered(bool registered);

        bool isRegistered();
        bool clientSentPass() const;
        bool clientSentNick() const;
        bool clientSentUser() const;

        void clientPassStatus(bool status);
        void clientNickStatus(bool status);
        void clientUserStatus(bool status);
        void clientRegisteredStatus(bool status);
        void updateRegisteredStatus();

        void    addClientMap(void);
        
        void     pass_command(std::string Newpassword);
        void    nick_command(std::string NewNick);
        void    user_command(std::string NewUser);
        const std::set<Channel *> &getChan() const;
        void addChan(Channel *chan);
        void removeChan(Channel *chan);
        bool isInChannel(const std::string &chanName) const;
};