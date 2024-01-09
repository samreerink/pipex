# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                          :+:    :+:              #
#                                                      +:+                     #
#    By: sreerink <sreerink@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/04/18 02:47:30 by sreerink      #+#    #+#                  #
#    Updated: 2024/01/09 19:18:04 by sreerink      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= 		pipex

RM= 		rm -rf

FLAGS= 		-Wall -Werror -Wextra

SRCS= 		pipex.c pipex_utils.c pipex_error.c

OBJ= 	$(SRCS:.c=.o)

LIBFT=		./Libft/libft.a

all:		$(NAME)

%.o:		%.c
	$(CC) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C ./Libft

$(NAME): 	$(LIBFT) $(OBJ)
	$(CC) $(OBJ) -L./Libft -lft -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./Libft clean

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) -C ./Libft fclean

re:		fclean $(NAME)

.PHONY:	all clean fclean re
