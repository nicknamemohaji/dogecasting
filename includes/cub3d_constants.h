/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_constants.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:03:35 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/28 16:57:07 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CONSTANTS_H
# define CUB3D_CONSTANTS_H

# include "cub3d_error.h"

// screen size
# define SCREEN_WIDTH 2000
# define SCREEN_HEIGTH 1000
# define MINIMAP_DIVIDER 8
# define POV 0.6

// include PI
# include <math.h>

// movement constants
// move: 1/20 tiles
# define MOVE_SPEED 0.08
# define MOVE_MAX 0.1
// rotate: 5 degrees
// fuck norm
// # define ROTATE_SPEED M_PI / 36.0

// mlx hook constants
# define ON_KEYDOWN 2
# define ON_MOUSEDOWN 4
# define ON_MOUSEMOVE 6
# define ON_DESTROY 17

// mlx hook masks
# define NOEVENTMASK 0L

// mlx mouse buttons
# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

// mlx keycodes
# define KEYBOARD_ESC 53
# define KEYBOARD_W 13
# define KEYBOARD_A 0
# define KEYBOARD_S 1
# define KEYBOARD_D 2
# define KEYBOARD_LEFT 123
# define KEYBOARD_RIGHT 124

// constants for direction
typedef enum e_dir
{
	UNDEFINED = -1,
	DIR_N = 0,
	DIR_S = 1,
	DIR_W = 2,
	DIR_E = 3
}	t_dir;

// constants for layer
typedef enum e_layer
{
	LAYER_EMPTY = 0,
	LAYER_BG = 1,
	LAYER_RENDER = 2,
	LAYER_MAP = 3,
	LAYER_RAY = 4
}	t_layer;

# define MAP_FILE_EXT ".cub"
# define VALID_TEXTURE_EXT ".xpm"

# define TEXTURE_AMOUNT 4 
# define NORTH "NO "
# define SOUTH "SO "
# define WEST "WE "
# define EAST "EA "
# define FLOOR_COLOR "F "
# define CEILING_COLOR "C "
# define DIR_KEY_LEN 3
# define COLOR_KEY_LEN 2

#endif
