INCLUDE = includes/irc.hpp

SRC = sources/main.cpp\
		sources/serveur.cpp\
			sources/socket.cpp \
				sources/command.cpp \
					sources/clients.cpp \
						sources/channel.cpp\
							sources/exception.cpp\
								sources/error_message.cpp\

NAME = ircserv

OBJ = $(SRC:.cpp=.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

DEP = $(SRC:.cpp=.d)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)
