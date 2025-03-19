#pragma once
#include <map>
#include "clients.hpp"
#include "irc.hpp"
#include <string>
#include <vector>
#include <set>


class clients;

class Channel 
{
     public:
        Channel(std::string &name);
        ~Channel();
        const std::string &getName() const;

        void addClient(clients *client);
        void supprimClient(clients *client);
        bool clientInChannel(clients *client) const;
        const std::vector<clients *> &getClients() const;

        void addMode(char mode);
        void removeMode(char mode);
        bool hasMode(char mode) const;

        void setKey(const std::string &key);
        void removeKey();
        bool hasKey() const;
        bool keyIsValid(const std::string &key) const;
        const std::string &getKey() const;

        void addTopic(const std::string &topic);
        const std::string &getTopic() const;
        bool hasTopic() const;

        void setLimit(int limit);
        void removeLimit();
        int getLimit() const;
        bool isFull() const;

        void addOperator(clients *client);
        void removeOperator(clients *client);
        bool isOperator(clients *client) const;


        void addInvite(clients *client);
        void removeInvite(clients *client);
        bool isInvited(clients *client) const;
        //join
        void listClientInChannel(clients *client, Channel *channel);
        void    command_join(clients *client, const std::vector<std::string> &arg);
        std::vector<std::string> splitArgJ(const std::string str, char separator);


     private:
        std::string _name;
        std::vector<clients *> _clients;
        std::set<char> _modes;
        std::string _key;
        std::string _topic;
        bool _hasTopic;
        int _limit;
        std::set<clients *> _operators;
        std::set<clients *> _invites;
        std::map<std::string, Channel*> _channels;

};