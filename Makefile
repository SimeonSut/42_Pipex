CC = cc

FLAGS = -Wall -Wextra -Werror -g

SRC = main.c parsing.c children.c piping.c utils.c cleaning.c

SRC_BONUS = main_bonus.c parsing.c piping_bonus.c children_bonus.c utils.c cleaning.c

NAME = pipex

all: $(NAME)

$(NAME): $(SRC) libft
	@$(CC) $(FLAGS) $(SRC) libft.a -o $(NAME)

bonus: $(SRC_BONUS) libft
	@$(CC) $(FLAGS) $(SRC_BONUS) libft.a -o $(NAME)

libft:
	@cd Libft ; make ; make clean ; mv 'libft.a' ..

clean:
	@rm -f libft.a

fclean: clean
	@rm -f $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus
