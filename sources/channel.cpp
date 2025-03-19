#include"../includes/irc.hpp"

Channel::Channel(std::string &name) : _name(name), _hasTopic(false), _limit(0)
{}

Channel::~Channel()
{
	for(std::vector<clients *>::iterator it = _clients.begin(); it != _clients.end(); it++)
		(*it)->removeChan(this);
	_clients.clear();
}

const std::string &Channel::getName() const
{
    return _name;
}

void Channel::addClient(clients *client)
{
    if(!clientInChannel(client))
        _clients.push_back(client);
}

void Channel::supprimClient(clients *client)
{
    for(std::vector<clients *>::iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        if (*it == client)
        {
            _clients.erase(it);
            return;
        }
    }
}

bool Channel::clientInChannel(clients *client) const
{
    for(std::vector<clients *>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
    {
        if (*it == client)
            return true;
    }
    return false;
}

const std::vector<clients *> &Channel::getClients() const
{
    return _clients;
}

void Channel::addMode(char mode)
{
    _modes.insert(mode);
}

void Channel::removeMode(char mode)
{
    _modes.erase(mode);
}

bool Channel::hasMode(char mode) const
{
    return _modes.find(mode) != _modes.end();
}

void Channel::setKey(const std::string &key)
{
    _key = key;
}

void Channel::removeKey()
{
    _key.clear();
    _modes.erase('k');
}

bool Channel::keyIsValid(const std::string &key) const
{
    return _key == key;
}

bool Channel::hasKey() const
{
    return hasMode('k');
}

const std::string &Channel::getKey() const
{
    return _key;
}

void Channel::addTopic(const std::string &topic)
{
    _topic = topic;
    _hasTopic = true;
}

const std::string &Channel::getTopic() const
{
    return _topic;
}

bool Channel::hasTopic() const
{
    return _hasTopic;
}

void Channel::setLimit(int limit)
{
    _limit = limit;
}

void Channel::removeLimit()
{
    _limit = 0;
    _modes.erase('l');
}

int Channel::getLimit() const
{
    return _limit;
}

bool Channel::isFull() const
{
	return hasMode('l') && static_cast<int>(_clients.size()) >= _limit;
}

void Channel::addOperator(clients *client)
{
    _operators.insert(client);
}

void Channel::removeOperator(clients *client)
{
    _operators.erase(client);
}

bool Channel::isOperator(clients *client) const
{
    return _operators.find(client) != _operators.end();
}

void Channel::addInvite(clients *client)
{
    _invites.insert(client);
}

void Channel::removeInvite(clients *client)
{
    _invites.erase(client);
}

bool Channel::isInvited(clients *client) const
{
    return _invites.find(client) != _invites.end();
}