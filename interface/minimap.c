/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 07:29:57 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/04 08:35:04 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	interface_minimap(t_frame *frame, t_map const *map,
			const t_vector2d player_pos);
void	interface_fps_counter(t_frame *frame);

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

/*
TODO: include libft and use ft_ftoa
for now, use sprintf
*/
void	interface_fps_counter(t_frame *frame)
{
	static struct timeval	last_time = {0, 0};
	unsigned long long		timediff;
	struct timeval			current_time;
	char					str[50];

	gettimeofday(&current_time, NULL);
	if (last_time.tv_usec > current_time.tv_usec)
		timediff = 1;
	else
		timediff = 0;
	timediff = (current_time.tv_sec - last_time.tv_sec - timediff) * 1000 * 1000
		+ (timediff * 1000 * 1000 + current_time.tv_usec - last_time.tv_usec);
	last_time = current_time;
	if (timediff != 0)
	{
		mlx_string_put(frame->mlx, frame->window,
			0, SCREEN_HEIGTH - 20, 0x000000, "FPS: ");
		sprintf(str, "%f", 1000.0 * 1000.0 / timediff);
		mlx_string_put(frame->mlx, frame->window,
			50, SCREEN_HEIGTH - 20, 0x0000ff, str);
	}
}
