/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:37:41 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/04 03:52:17 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		cub3d(t_frame *frame);
static void	draw_ceilng_and_floor(t_frame *frame);

void	cub3d(t_frame *frame)
{
	const t_map			*map = &(frame->map);
	const t_vector2d	player_pos = frame->player_pos;
	const t_vector2d	player_dir = frame->player_dir;

	draw_ceilng_and_floor(frame);
	cub3d_render(frame, map, player_pos, player_dir);
	cub3d_minimap(frame, map, player_pos);
}

static void	draw_ceilng_and_floor(t_frame *frame)
{
	int		x;
	int		y;
	const t_texture	*texture = frame->map.textures[0];

	y = -1;

	while (++y < SCREEN_HEIGTH / 2)
	{
		// const double camZ = 0.5 * SCREEN_HEIGTH;
		// double p = camZ - (double) y;
		// double rowDist = camZ / p;

		// t_vector2d camera_ray1;
		// t_vector2d camera_ray2;
		// camera_ray1.x = frame->camera_dir.x - frame->player_dir.x;
		// camera_ray1.y = frame->camera_dir.y - frame->player_dir.y;
		// camera_ray2.x = frame->camera_dir.x + frame->player_dir.x;
		// camera_ray2.y = frame->camera_dir.y + frame->player_dir.y;

		// t_vector2d step;
		// step.x = (camera_ray2.x - camera_ray1.x) * rowDist / SCREEN_WIDTH;
		// step.y = (camera_ray2.y - camera_ray1.y) * rowDist / SCREEN_WIDTH;
		// t_vector2d floor;
		// floor.x = frame->player_pos.x + rowDist * camera_ray1.x;
		// floor.y = frame->player_pos.y + rowDist * camera_ray1.y;

		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			(void) texture;
			ft_mlx_image_put(frame, (t_vector2i){x,y}, 0x00ffff, LAYER_BG);
			ft_mlx_image_put(frame, (t_vector2i){x, (SCREEN_HEIGTH - 1 - y)}, 0xffff00, LAYER_BG);
			// t_vector2i	cell;
			// cell.x = (int)floor.x;
			// cell.y = (int)floor.y;

			// t_vector2i	texture_pos;
			// texture_pos.x = (int)(texture->width * (floor.x - cell.x)) & (texture->width - 1);
			// texture_pos.y = (int)(texture->height * (floor.y - cell.y)) & (texture->height - 1);

			// floor.x += step.x;
			// floor.y += step.y;

			// ft_mlx_image_put(frame, (t_vector2i){x,y}, ft_mlx_image_color(texture->image, texture_pos.x, texture_pos.y), LAYER_BG);
			// ft_mlx_image_put(frame, (t_vector2i){x, (SCREEN_HEIGTH - 1 - y)}, ft_mlx_image_color(texture->image, texture_pos.x, texture_pos.y), LAYER_BG);
		}
	}
}
