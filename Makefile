
NAME := cub3D

MLX_DIR := minilibx/

SOURCES :=	ft_mlx/mlx_setup.c \
			ft_mlx/mlx_image.c \
			ft_mlx/mlx_hook.c \
			ft_mlx/mlx_hook_2.c \
			ft_mlx/mlx_shape.c \
			raycast/ft_vector2.c \
			raycast/cub3d.c \
			raycast/render.c \
			raycast/render_texture.c \
			raycast/render_background.c \
			interface/interface.c \
			interface/minimap.c \
			main.c
OBJECTS := $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 #-g3 -fsanitize=address
HEADERS =  -I $(MLX_DIR) -I .
INCLUDES =	-L . -l mlx -l m \
			-framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): libmlx.dylib $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(INCLUDES)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $*.o

libmlx.dylib:
	@$(MAKE) -C $(MLX_DIR) all
	@cp $(MLX_DIR)libmlx.dylib .

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -f $(MLX_DIR)*.swiftsourceinfo
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -f libmlx.dylib
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
