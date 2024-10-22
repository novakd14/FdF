CC = cc
CFLAGS = -Wall -Wextra -Werror
TEST_CFLAGS = -g
CLIB_DIR = libft
CLIB = ft
MLX_LIB = -lmlx -lXext -lX11

NAME = fdf
SRCS = main.c
HEAD = fdf.h
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re test norm memleak

all: $(NAME)

$(NAME): $(OBJS) $(HEAD)
	make -C $(CLIB_DIR)
	$(CC) -o $@ $^ -L$(CLIB_DIR) -l$(CLIB) $(MLX_LIB)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	-./$<

norm:
	norminette

# memleak: $(NAME)
# 	valgrind -s --leak-check=full --show-leak-kinds=all ./$(TEST_NAME)
