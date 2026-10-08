NAME		= get_next_line.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

ifdef BUFFER_SIZE
BUFFER_FLAG	= -D BUFFER_SIZE=$(BUFFER_SIZE)
endif

SRCS		= get_next_line.c get_next_line_utils.c
OBJS		= $(SRCS:.c=.o)

BONUS_SRCS	= get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

TST_URL		= https://raw.githubusercontent.com/rdentato/tst/main/src/tst.h
TEST_DIR	= tests
TEST_BIN	= $(TEST_DIR)/get_next_line_test
BONUS_TEST_BIN	= $(TEST_DIR)/get_next_line_bonus_test

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(BUFFER_FLAG) -c $< -o $@

download_tst:
	curl -o $(TEST_DIR)/tst.h $(TST_URL)

test:
	$(CC) $(CFLAGS) -Wno-unused-parameter $(BUFFER_FLAG) $(SRCS) $(TEST_DIR)/get_next_line_test.c -o $(TEST_BIN)
	./$(TEST_BIN)

test_bonus:
	$(CC) $(CFLAGS) -Wno-unused-parameter $(BUFFER_FLAG) $(BONUS_SRCS) $(TEST_DIR)/get_next_line_bonus_test.c -o $(BONUS_TEST_BIN)
	./$(BONUS_TEST_BIN)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(TEST_BIN) $(BONUS_TEST_BIN)

re: fclean all

.PHONY: all bonus clean fclean re test test_bonus download_tst
