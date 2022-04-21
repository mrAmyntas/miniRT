NAME = miniRT
MLX_NAME = libmlx42.a
CC = gcc
LIBFT_NAME = libft/libft.a
FLAGS = #-Wall -Werror -Wextra
OBJ_DIR = obj/
SRC_DIR = src/
LIBFT_DIR =	libft/
SRC =	src/main.c\
		src/colours.c\
		src/get_scene.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\
		src/plane.c

INC = 	inc/miniRT.h\
		libft/libft.h

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(LIBFT_NAME) $(MLX_NAME) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME)
	$(CC) $(OBJ) MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

$(MLX_NAME):
	make -C ./mlx42

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	$(CC) -c $(FLAGS) -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT_NAME): $(LIBFT_DIR)*.c $(LIBFT_DIR)
	make -C libft

clean:
	rm -f obj/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re