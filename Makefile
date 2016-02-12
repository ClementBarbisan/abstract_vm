NAME = avm

SRC = abstract.cpp\
		parser.cpp\
		commands.cpp\
		stack.cpp\
		lexer.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $@ $^

%.o: %.cpp
	g++ -o $@ -c $^ -Wall -Werror -Wextra -I./includes/

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
