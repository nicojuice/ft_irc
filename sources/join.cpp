#include "../includes/irc.hpp"

std::vector<std::string> splitArgJ(const std::string str, char separator)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end;

    while((end = str.find(separator, start)) != std::string::npos)
    {
        if(end != start)
            tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    if(start < str.size())
        tokens.push_back(str.substr(start));
    return tokens;
}

void listClientInChannel(clients *client, Channel *channel)
{
    std::string listNick;
    (void) client;
    const std::vector<clients*> &clients = channel->getClients();
    for(size_t i = 0; i < clients.size(); ++i)
    {
        if(channel->isOperator(clients[i]))
            listNick += "@";
        listNick += clients[i]->getNickname() + " ";
    }
    //envoie list client RPL
    std::cout << "Liste des clients dans le channel : " << listNick << std::endl;

}

void command_join(clients *client, std::string &arg)
{
    if(arg.size() < 2)
        throw ErrorCmd(client,"JOIN",461);
    std::vector<std::string> channelNames = splitArgJ(arg[1], ',');
    std::vector<std::string> key;
    if(arg.size() >= 3)
        key = splitArgJ(arg[2], ',');
    for(size_t i = 0; i < channelNames.size(); ++i)
    {
        std::string channelName = channelNames[i];
        std::string key = "";
        if(key.size() > 0)
            key = key[i];
        if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&'))
        {
            throw ErrorCmd(client,"JOIN",476);
            continue;
        }
        Channel *channel = NULL;
        if(_channels.find(channelName) == _channels.end())
        {
            channel = new (std::nothrow) Channel(channelName);
            if(channel == NULL)
            {
                std::cout << "Error: memory could not be allocated for channel" << std::endl;
                continue;
            }
            _channels[channelName] = channel;
            channel->addOperator(client);
        }
        else
        {
            channel = _channels[channelName];
            if(channel->hasMode('i') && !channel->isInvited(client))
            {
                throw ErrorCmd(client,"JOIN",473);
                continue;
            }
            if (channel->hasMode('k') && !channel->keyIsValid(key))
            {
                throw ErrorCmd(client,"JOIN",475);
                continue;
            }
            if(channel->isFull())
            {
                throw ErrorCmd(client,"JOIN",471);
                continue;
            }
            channel->addClient(client);
            client->addChan(channel);
            channel->removeInvite(client);
            //message nouveau client a faire
            listClientInChannel(client, channel);
        }       
    }
}