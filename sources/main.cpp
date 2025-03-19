#include "../includes/irc.hpp"

//politique de mdp a faire!

bool isDigits(const std::string& str) {
    if (str.empty()) return false;

    size_t i = 0;
    while (i < str.length()) {
        if (!std::isdigit(str[i])) {
            return false;
        }
        i++;
    }
    return true;
}

void    error_handler(int i)
{
    if (i == 1)
        throw Exception("Bad arguments");
    if (i == 2)
        throw Exception("Bad port");
    exit (0);    
}

int main(int ac, char **av)
{
    try
    {
        if (ac != 3)
            error_handler(1);
        serveur test(av[1],av[2]);
        while(1)
            ;
        return(0);
    }
    catch(const std::exception& e)
    {
        std::cerr << RED <<"ERROR -> " << RESET << e.what() << '\n';
    }
    return (0);
}