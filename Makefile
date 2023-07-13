# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sreerink <sreerink@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/04/18 02:47:30 by sreerink      #+#    #+#                  #
#    Updated: 2023/04/18 02:47:58 by sreerink      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= 		pipex

RM= 		rm -rf

FLAGS= 		-Wall -Werror -Wextra

SRCS= 		pipex.c pipex_utils.c

OBJ= 	$(SRCS:.c=.o)

LIBFT=		./Libft/libft.a

all:		$(NAME)

%.o:		%.c
	$(CC) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C ./Libft

$(NAME): 	$(LIBFT) $(OBJ)
	$(CC) $(LIBFT) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./Libft clean

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) -C ./Libft fclean

re:		fclean $(NAME)

.PHONY:	all clean fclean re
