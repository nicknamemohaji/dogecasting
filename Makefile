
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
HEADERS =  -I $(MLX_DIR) -I . -I libft/includes
INCLUDES =	-L . -l mlx -l m \
			-framework OpenGL -framework AppKit
MLX_INCLUDES = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): libmlx.dylib $(OBJECTS) libft.a
	$(CC) $(CFLAGS) $^ -o $(NAME) $(INCLUDES) $(LIBFT_INCLUDE)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $*.o

libft.a:
	@$(MAKE) -C libft all
	mv libft/libft.a .

libmlx.dylib:
	@$(MAKE) -C $(MLX_DIR) all
	@cp $(MLX_DIR)libmlx.dylib .

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -f $(MLX_DIR)*.swiftsourceinfo
	@rm -rf $(OBJECTS)
	@$(MAKE) -C libft clean
	
fclean: clean
	@rm -f libmlx.dylib
	@rm -rf $(NAME)
	@rm -rf libft.a

re: fclean all

.PHONY: all clean fclean re bonus
