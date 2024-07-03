/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 18:02:01 by kyungjle          #+#    #+#             */
/*   Updated: 2024/06/17 06:40:46 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TYPES_H
# define CUB3D_TYPES_H

# include "cub3d_constants.h"

// mlx image info struct
typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

// struct for texture
typedef struct s_texture
{
	t_image	*image;
	int		height;
	int		width;
}	t_texture;

// map structure
typedef struct s_map
{
	t_texture	**textures;
	int			**map;
	int			map_w;
	int			map_h;
	int			minimap_divider;
}	t_map;

// vector structure
typedef struct s_vector2d
{
	double	x;
	double	y;
}	t_vector2d;
typedef struct s_vector2i
{
	int	x;
	int	y;
}	t_vector2i;

// struct for dda algorithm
typedef struct s_dda
{
	t_vector2d	dist;
	double		dist_plane;

	t_vector2d	dist_delta;
	t_vector2d	ray_dir;
	t_vector2i	step;
	int			side;
}	t_dda;

// struct for affine texture mapping
typedef struct s_render_params
{
	int			line_height;
	int			draw_start;
	int			draw_end;

	int			x;
	t_dda		dda_result;
	t_texture	*texture;

	double		wall_pos;
	double		step;
}	t_render_params;

// mlx frame struct
typedef struct s_frame {
	void		*mlx;
	void		*window;
	t_image		*image;

	t_map		map;
	t_vector2d	player_dir;
	t_vector2d	player_pos;
	t_vector2d	camera_dir;

	t_dda		dda[SCREEN_WIDTH];
	int			screen[SCREEN_WIDTH][SCREEN_HEIGTH];
	void		(*draw)(struct s_frame *frame);
}	t_frame;

#endif
