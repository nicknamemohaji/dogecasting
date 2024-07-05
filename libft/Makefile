NAME= libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS := $(shell find . -name ft_\*.c | grep -v bonus)

SRCS := get_next_line/get_next_line.c \
		$(SRCS) \
		$(shell find addons -name ft_\*.c)
OBJS := $(SRCS:.c=.o)

BONUS_SRCS := $(shell find . -name ft_\*_bonus.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(BONUS_OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(@:.o=.c) -o $@ -I includes

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus: $(OBJS) $(BONUS_OBJS)
	ar rc $(NAME) $(OBJS) $(BONUS_OBJS) 

$(BONUS_OBJS): $(BONUS_SRCS)
	$(CC) $(CFLAGS) -c $(@:.o=.c) -o $@ -I includes

.PHONY: all clean fclean re bonus

