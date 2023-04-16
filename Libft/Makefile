NAME= 		libft.a

HEADER=		libft.h

RM= 		rm -f

FLAGS= 		-Wall -Werror -Wextra

SRCS= 		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
			ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
			ft_memcpy.c ft_memmove.c ft_toupper.c ft_tolower.c \
			ft_strncmp.c ft_strchr.c ft_strrchr.c ft_memchr.c \
			ft_strlcpy.c ft_memcmp.c ft_atoi.c ft_calloc.c \
			ft_strdup.c ft_strdup.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strlcat.c ft_substr.c ft_strjoin.c ft_strtrim.c \
			ft_strmapi.c ft_striteri.c ft_split.c ft_strnstr.c \
			ft_itoa.c ft_strjoin_free.c

SRCS_BONUS=		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECT= 	$(SRCS:.c=.o)

OBJECT_BONUS=	$(SRCS_BONUS:.c=.o)

all:		$(NAME)

$(NAME): 	$(OBJECT)
			ar rcs $@ $^

bonus:		$(NAME) $(OBJECT_BONUS)
			ar rcs $< $(OBJECT_BONUS)

%.o:		%.c $(HEADER)
			$(CC) -c $(FLAGS) -o $@ $<

clean:
			$(RM) $(OBJECT) $(OBJECT_BONUS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:	all clean fclean re bonus
