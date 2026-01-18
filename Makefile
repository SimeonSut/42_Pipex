CC = cc

FLAGS = -Wall -Wextra -Werror -g

SRC = main.c parsing.c piping.c utils.c cleaning.c

NAME = pipex

all: $(NAME)

$(NAME): $(SRC) libft
	@$(CC) $(CFLAGS) $(SRC) libft.a -o $(NAME)

libft:
	@cd Libft ; make ; make clean ; mv 'libft.a' ..

clean:
	@rm -f libft.a

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
