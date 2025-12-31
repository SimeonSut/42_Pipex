CC = cc

FLAGS = -Wall -Wextra -Werror

SRC = main.c ft_checking.c ft_parsing.c cleaning.c

HDR = pipex.h

NAME = pipex

all: $(NAME)

$(NAME): $(SRC) libft
	@$(CC) $(CFLAGS) $(SRC) libft.a -g -o $(NAME)

libft:
	@cd Libft ; make ; make clean ; mv 'libft.a' ..

clean:
	@rm -f libft.a

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
