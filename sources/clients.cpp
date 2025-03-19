#include "../includes/irc.hpp"
#include "../includes/clients.hpp"
#include "../includes/serveur.hpp"
#include "../includes/exception.hpp"


clients::clients(int socket, serveur *_serveur) : _socket(socket), _registered(false), _clientSentPass(false),
         _clientSentNick(false), _clientSentUser(false), _serveur(_serveur)
{}

clients::clients() : _socket(-1), _registered(false), _clientSentPass(false),
         _clientSentNick(false), _clientSentUser(false), _serveur(NULL)
{}

const std::string &clients::getNickname() const
{
    return _nickname;
}

const std::string &clients::getUsername() const
{
    return _username;
}

const std::string &clients::getRealname() const
{
    return _realname;
}

const std::string &clients::getHostname() const
{
    return _hostname;
}

const std::string &clients::getServername() const
{
    return _servername;
}

const int &clients::getSocketname() const
{
    return _socket;
}

void clients::setSocket(int socket)
{
    _socket = socket;
}

void clients::setNickname(const std::string &nickname)
{
    _nickname = nickname;
}

void clients::setUsername(const std::string &username)
{
    _username = username;
}

void clients::setRealname(const std::string &realname)
{
    _realname = realname;
}

void clients::setHostname(const std::string &hostname)
{
    _hostname = hostname;
}

void clients::setServername(const std::string &servername)
{
    _servername = servername;
}

void clients::setRegistered(bool registered)
{
    _registered = registered;
}

bool clients::isRegistered()
{
    return _registered;
}

bool clients::clientSentPass() const
{
    return _clientSentPass;
}

bool clients::clientSentNick() const
{
    return _clientSentNick;
}

bool clients::clientSentUser() const
{
    return _clientSentUser;
}

void clients::clientPassStatus(bool status)
{
    _clientSentPass = status;

}

void clients::clientNickStatus(bool status)
{
    _clientSentNick = status;
}

void clients::clientUserStatus(bool status)
{
    _clientSentUser = status;
}

void clients::clientRegisteredStatus(bool status)
{
    _registered = status;
}

void clients::updateRegisteredStatus()
{
    if(_clientSentPass && _clientSentNick && _clientSentUser)
        _registered = true;
    else 
        _registered = false;
}

// int    clients::pass_command(std::string Newpassword)
// {
//     std::cout << "welcome to pass \n";
//     if (Newpassword.compare(_serveur->serv_password) == 1)
//         return (0);
//     return (1);
// }
void    clients::nick_command(std::string NewNick)
{
    this->setNickname(NewNick);
}
void    clients::user_command(std::string NewUser)
{
    this->setUsername(NewUser);
}

void clients::addChan(Channel *chan) 
{
	_chan.insert(chan);
}

void clients::removeChan(Channel *chan) 
{
	_chan.erase(chan);
}

bool clients::isInChannel(const std::string &chanName) const
{
	for(std::set<Channel *>::iterator it = _chan.begin(); it != _chan.end(); it++)
	{
		if ((*it)->getName() == chanName)
			return true;
	}
	return false;
}