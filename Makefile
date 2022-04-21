NAME = miniRT
MLX_NAME = libmlx42.a
CC = gcc
FLAGS = -Wall -Werror -Wextra
OBJ_DIR = obj/
SRC_DIR = src/
SRC =	src/main.c

INC = 	inc/miniRT.h

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(MLX_NAME) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) MLX42/libmlx42.a -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

$(MLX_NAME):
	make -C ./mlx42

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	$(CC) -c $(FLAGS) -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f obj/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re