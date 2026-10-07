NAME		= get_next_line.a

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

ifdef BUFFER_SIZE
BUFFER_FLAG	= -D BUFFER_SIZE=$(BUFFER_SIZE)
endif

SRCS		= get_next_line.c get_next_line_utils.c
OBJS		= $(SRCS:.c=.o)

BONUS_SRCS	= get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(BUFFER_FLAG) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
