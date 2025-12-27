CC = cc

FLAGS = -Wall -Wextra -Werror

SRC = main.c 

#SRC_BONUS =

HDR = pipex.h

#HDR_BONUS = 

NAME = pipex

#NAME_BONUS = 

all: $(NAME)

$(NAME): $(SRC) libft
	@$(CC) $(CFLAGS) $(SRC) libft.a -g -o $(NAME)

#bonus: libft
#	@$(CC) $(CFLAGS) $(SRC_BONUS) libft.a -g -o $(NAME_BONUS)

libft:
	@cd Libft ; make ; make clean ; mv 'libft.a' ..

clean:
	@rm -f libft.a

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
