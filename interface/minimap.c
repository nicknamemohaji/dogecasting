/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 07:29:57 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/20 13:57:40 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	interface_minimap(t_frame *frame, t_map const *map,
			const t_vector2d player_pos);

void	interface_minimap(t_frame *frame, t_map const *map,
			const t_vector2d player_pos)
{
	int			x;
	int			y;
	int			color;
	const int	minimap_size = 200 / map->map_w;

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
			ft_mlx_draw_rectangle(frame, minimap_size,
				color, (t_vector2i){x * minimap_size, y * minimap_size});
		}
	}
	ft_mlx_draw_rectangle(frame, minimap_size / 2,
		0x00ff00, (t_vector2i){
		(int)(player_pos.x * minimap_size), (int)(player_pos.y * minimap_size)
	});
}
