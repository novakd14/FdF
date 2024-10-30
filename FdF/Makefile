CC = cc
CFLAGS = -Wall -Wextra -Werror
TEST_CFLAGS = -g
CLIB_DIR = libft
CLIB = ft
MLX_LIB = -lmlx -lXext -lX11

NAME = fdf
SRCS = main.c load_map.c expand_map.c setup_projection.c scale_projection.c \
		setup_display.c map_to_image.c setup_events.c free_all.c utils.c
HEAD = fdf.h
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re test norm memleak

all: $(NAME)

$(NAME): $(OBJS) $(HEAD)
	make -C $(CLIB_DIR)
	$(CC) $(TEST_CFLAGS) -o $@ $^ -L$(CLIB_DIR) -l$(CLIB) $(MLX_LIB)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	-./$< $(ARG1) $(ARG2) $(ARG3)

norm:
	norminette

memleak: $(NAME)
	valgrind -s --leak-check=full --show-leak-kinds=all ./$< $(ARG1) $(ARG2) $(ARG3)
