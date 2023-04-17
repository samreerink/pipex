NAME= 		pipex

RM= 		rm -rf

FLAGS= 		-Wall -Werror -Wextra

SRCS= 		pipex.c find_path_env.c

OBJ= 	$(SRCS:.c=.o)

LIBFT=		./libft/libft.a

all:		$(NAME)

%.o:		%.c
	$(CC) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): 	$(LIBFT) $(OBJ)
	$(CC) $(LIBFT) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./libft clean

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) -C ./libft fclean

re:		fclean $(NAME)

.PHONY:	all clean fclean re
