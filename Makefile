# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/13 12:23:51 by kyungjle          #+#    #+#              #
#    Updated: 2024/07/03 14:47:36 by kyungjle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

MLX_DIR := minilibx/

SOURCES :=	ft_mlx/mlx_setup.c \
			ft_mlx/mlx_image.c \
			ft_mlx/mlx_hook.c \
			ft_mlx/mlx_hook_2.c \
			raycast/cub3d.c \
			raycast/minimap.c \
			raycast/ft_vector2.c \
			raycast/render_dda.c \
			raycast/render_texture.c \
			main.c
OBJECTS := $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
HEADERS =  -I $(LIBFT_DIR)headers/ -I $(MLX_DIR) -I .
INCLUDES =	-L . -l ft -l mlx -l m \
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
