NAME = miniRT
BONUS_NAME = miniRT_bonus
MLX_NAME = libmlx42.a
CC = gcc
LIBFT_NAME = libft/libft.a
FLAGS = -Wall -Werror -Wextra
#FLAGS += -fsanitize=address
OBJ_DIR = obj/
BONUS_OBJ_DIR = bonus/obj/
SRC_DIR = src/
BONUS_SRC_DIR = bonus/
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
		src/render_utils.c\
		src/light.c\
		src/calculate_hsl.c\
		src/ray.c\
		src/calc_camray_angles.c\
		src/utils.c

BONUS =	bonus/main.c\
		bonus/get_scene.c\
		bonus/get_scene_objects.c\
		bonus/get_scene_elements.c\
		bonus/plane.c\
		bonus/sphere.c\
		bonus/vector_math.c\
		bonus/vector_math2.c\
		bonus/cylinder.c\
		bonus/cylinder_calc.c\
		bonus/matrices.c\
		bonus/render.c\
		bonus/render_utils.c\
		bonus/light.c\
		bonus/calculate_hsl.c\
		bonus/ray.c\
		bonus/calc_camray_angles.c\
		bonus/disc.c\
		bonus/torus.c\
		bonus/torus_calc.c\
		bonus/torus_calc2.c\
		bonus/checkerboard_pl_di.c\
		bonus/checkerboard_cy_tor.c\
		bonus/get_scene_objects2.c\
		bonus/utils.c


INC = 	inc/miniRT.h\
		libft/libft.h\
		inc/scenes.h\
		inc/vectors.h

INC_BONUS = bonus/inc/miniRT.h\
			libft/libft.h\
			bonus/inc/scenes.h\
			bonus/inc/vectors.h

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_BONUS = $(BONUS:$(BONUS_SRC_DIR)%.c=$(BONUS_OBJ_DIR)%.o)

all: $(LIBFT_NAME) $(MLX_NAME) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ) $(LIBFT_NAME)
	$(CC) $(OBJ) $(FLAGS) MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)
#	$(CC) $(OBJ) $(FLAGS) MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/usr/local/cellar/glfw/3.3.7/lib/" -o $(NAME)

$(MLX_NAME):
	make -C ./mlx42

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) -c $(FLAGS) -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

$(BONUS_OBJ_DIR):
	mkdir -p $@

$(LIBFT_NAME): $(LIBFT_DIR)*.c $(LIBFT_DIR) libft/libft.h
	make -C libft

$(BONUS_NAME): $(OBJ_BONUS) $(LIBFT_NAME)
	$(CC) $(OBJ_BONUS) $(FLAGS) MLX42/libmlx42.a -lft -L ./libft -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(BONUS_NAME)

$(OBJ_BONUS): $(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c $(INC_BONUS)
	$(CC) -c $(FLAGS) -o $@ $<


bonus: $(LIBFT_NAME) $(MLX_NAME) $(BONUS_OBJ_DIR) $(BONUS_NAME)

clean:
	rm -f obj/*.o
	rm -f bonus/obj/*.o
	rm -f libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	rm -f $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re