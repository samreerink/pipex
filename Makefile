NAME= 		pipex.a

HEADER=		pipex.h

RM= 		rm -f

FLAGS= 		-Wall -Werror -Wextra

SRCS= 		pipex.c find_path_env.c

OBJECT= 	$(SRCS:.c=.o)


all:		$(NAME)

$(NAME): 	$(OBJECT)
			ar rcs $@ $^

%.o:		%.c $(HEADER)
			$(CC) -c $(FLAGS) -o $@ $<

clean:
			$(RM) $(OBJECT)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:	all clean fclean re
