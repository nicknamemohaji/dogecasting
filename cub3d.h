/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:48:25 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/04 06:27:53 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/***** library import ******/
// open
# include <fcntl.h>
// close, write
# include <unistd.h>
// malloc, free, exit
# include <stdlib.h>
// printf, perror, strerror
# include <stdio.h>
// standard math library header
# include <math.h>
// mlx library header
# include "mlx.h"

/********* custom import ********/
// types header
# include "cub3d_types.h"
// constants header
# include "cub3d_constants.h"

/*********** ft_mlx ************/
// mlx_image.c

void			ft_mlx_image_put(t_frame *frame, t_vector2i pos, int color);
unsigned int	ft_mlx_image_color(t_image *img, int x, int y);
int				ft_mlx_render(t_frame *frame);

// mlx_setup.c

void			ft_mlx_setup(t_frame *frame, t_image *img);
void			ft_mlx_setup_image(t_frame *frame, t_image *img);

// mlx_hook.c

int				ft_mlx_destroy(t_frame *frame);
int				ft_mlx_event_key(int keycode, t_frame *frame);

// mlx_hook2.c

int				ft_mlx_event_mouse(int button, int x, int y, t_frame *frame);

/*********** raycast **************/
// ft_vector2.c
t_vector2d		ft_vector2d_add(t_vector2d n1, t_vector2d n2);
t_vector2d		ft_vector2d_mul(t_vector2d vec, double scalar);
t_vector2d		ft_vector2d_rotate(t_vector2d vec, double rad);
t_vector2i		ft_vector2i_add(t_vector2i n1, t_vector2i n2);

// cub3d.c

void			cub3d(t_frame *frame);

// render_dda.c

void			cub3d_render(t_frame *frame, const t_map *map,
					const t_vector2d player_pos, const t_vector2d player_dir);

// render_texture.c

void			cub3d_render_draw(t_frame *frame,
					t_render_params const *params);

// minimap.c

void			cub3d_minimap(t_frame *frame, const t_map *map,
					const t_vector2d player_pos);

#endif
