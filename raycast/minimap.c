/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 02:27:52 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/04 03:52:46 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		cub3d_minimap(t_frame *frame, const t_map *map,
				const t_vector2d player_pos);
void		cub3d_minimap_ray(t_frame *frame, t_dda *dda,
				t_vector2i ray_pos, t_vector2d player_pos);
static void	draw_rectangle(t_frame *frame, unsigned int color, t_vector2i pos);
static void	draw_circle(t_frame *frame, unsigned int color, t_vector2d pos);

void	cub3d_minimap(t_frame *frame, const t_map *map,
			const t_vector2d player_pos)
{
	int	x;
	int	y;
	int	color;

	// TODO 시점에 맞춰 미니맵 회전
	y = -1;
	while (++y < map->map_h)
	{
		x = -1;
		while (++x < map->map_w)
		{
			if (map->map[y][x] != 0)
				color = 0xffffff;
			else
				color = 0x333333;
			draw_rectangle(frame, color, (t_vector2i){x, y});
		}
	}
	draw_circle(frame, 0xcccc00, player_pos);
}

void	cub3d_minimap_ray(t_frame *frame, t_dda *dda,
			t_vector2i ray_pos, t_vector2d p_pos)
{
	int			x;
	int			y;

	// TODO fix ray 
	while ((int) p_pos.x != ray_pos.x && (int) p_pos.y != ray_pos.y)
	{
		x = (int)(p_pos.x * frame->map.minimap_divider);
		y = (int)(p_pos.y * frame->map.minimap_divider);
		ft_mlx_image_put(frame, (t_vector2i){x, y}, 0xff0000, LAYER_RAY);
		p_pos.x += dda->ray_dir.x / (double) frame->map.minimap_divider;
		p_pos.y += dda->ray_dir.y / (double) frame->map.minimap_divider;
	}
}

static void	draw_rectangle(t_frame *frame, unsigned int color, t_vector2i pos)
{
	t_vector2i			screen_pos;

	screen_pos.x = -1;
	while (++screen_pos.x < frame->map.minimap_divider)
	{
		screen_pos.y = -1;
		while (++screen_pos.y < frame->map.minimap_divider)
		{
			ft_mlx_image_put(frame,
				(t_vector2i){
				pos.x * frame->map.minimap_divider + screen_pos.x,
				pos.y * frame->map.minimap_divider + screen_pos.y,
			},
				color, LAYER_MAP);
		}
	}
}

static void	draw_circle(t_frame *frame, unsigned int color, t_vector2d p_pos)
{
	t_vector2i	screen_pos;
	t_vector2i	pos;
	const int	divider = frame->map.minimap_divider / 2;

	screen_pos.x = (int) p_pos.x * divider * 2 + divider;
	screen_pos.y = (int) p_pos.y * divider * 2 + divider;
	pos.x = screen_pos.x - divider;
	while (++pos.x < screen_pos.x + divider)
	{
		pos.y = screen_pos.y - divider;
		while (++pos.y < screen_pos.y + divider)
		{
			if ((pos.x - screen_pos.x) * (pos.x - screen_pos.x)
				+ (pos.y - screen_pos.y) * (pos.y - screen_pos.y)
				<= divider * divider)
			{
				ft_mlx_image_put(
					frame,
					(t_vector2i){pos.x, pos.y},
					color, LAYER_MAP);
			}
		}
	}
}
