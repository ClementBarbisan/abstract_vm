NAME = avm

SRC = Abstract.cpp\
	  	QueueFunctions.cpp\
		OperandFactory.cpp\
		Commands.cpp\
		Parser.cpp\
		StackValue.cpp\
		Lexer.cpp

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
