NAME = miniRT
MLX_NAME = libmlx42.a
CC = gcc
LIBFT_NAME = libft/libft.a
FLAGS = #-Wall -Werror -Wextra
#FLAGS += -fsanitize=address
OBJ_DIR = obj/
SRC_DIR = src/
GNL_DIR = gnl/

LIBFT_DIR =	libft/
SRC =	src/main.c\
		src/get_scene.c\
		src/get_scene_objects.c\
		src/get_scene_elements.c\
		src/plane.c\
		src/sphere.c\
		src/vector_math.c\
		src/vector_math2.c\
		src/cylinder.c\
		src/cylinder_calc.c\
		src/matrices.c\
		src/render.c\
		src/light.c\
		src/calculate_hsl.c\
		src/ray.c\
		src/calc_camray_angles.c

INC = 	inc/miniRT.h\
		libft/libft.h\
		inc/scenes.h\
		inc/vectors.h

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(LIBFT_NAME) $(MLX_NAME) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME)
	$(CC) $(OBJ) $(FLAGS) MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

$(MLX_NAME):
	make -C ./mlx42

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) -c $(FLAGS) -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT_NAME): $(LIBFT_DIR)*.c $(LIBFT_DIR) libft/libft.h
	make -C libft

clean:
	rm -f obj/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re