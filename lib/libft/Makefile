SRCS			= ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c ft_isalnum.c \
			ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
			ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			ft_lstiter.c ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_printf.c \
			ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
			ft_split.c ft_strchr.c ft_strcmp.c ft_strcspn.c ft_strdup.c \
			ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strpbrk.c ft_strrchr.c \
			ft_strspn.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
			ft_isspace.c get_next_line.c ft_dprintf.c
OBJS 			= $(SRCS:.c=.o)
CFLAGS			= -Wall -Wextra -Werror
ARC				= ar rc
NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
	@$(ARC) $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)

%.o 			: %.c libft.h
	@$(CC) $(CFLAGS) -o $@ -c $<

fclean:			clean
	@$(RM) $(NAME)
				
re:	fclean all