/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:39:48 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 15:42:50 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

void	validate_map(t_frame *frame, t_map *map);
t_bool	has_zero_in_map_outline(t_map *map, int y, int x);
t_bool	has_space_around_zero(t_map *map, int y, int x);
t_bool	player_pos_in_outline(t_map *map, t_vector2i pos, t_vector2i curr);
t_bool	has_space_around_player_pos(t_map *map, int y, int x);

void	validate_map(t_frame *frame, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			if (has_zero_in_map_outline(map, i, j)
				|| has_space_around_zero(map, i, j))
				throw_parse_error(ERR_MAP ERR_MAP_SURROUND);
			if (player_pos_in_outline(map, (t_vector2i){frame->player_pos.x,
					frame->player_pos.y}, (t_vector2i){j, i}))
				throw_parse_error(ERR_MAP ERR_MAP_PLAYER);
			if (i == frame->player_pos.y && j == frame->player_pos.x
				&& has_space_around_player_pos(map, i, j))
				throw_parse_error(ERR_MAP ERR_MAP_PLAYER);
			j++;
		}
		i++;
	}
}

t_bool	has_zero_in_map_outline(t_map *map, int y, int x)
{
	return (map->map[y][x] == 0
		&& (y == 0 || y == map->map_h - 1 || x == 0 || x == map->map_w -1));
}

t_bool	has_space_around_zero(t_map *map, int y, int x)
{
	return (map->map[y][x] == 0 &&
				(map->map[y - 1][x] > 1 || map->map[y + 1][x] > 1
					|| map->map[y][x - 1] > 1 || map->map[y][x + 1] > 1));
}

t_bool	player_pos_in_outline(t_map *map, t_vector2i pos, t_vector2i curr)
{
	return (curr.x == pos.x && curr.y == pos.y
		&& (pos.x == 0 || pos.x == map->map_w - 1
			|| pos.y == 0 || pos.y == map->map_h - 1));
}

t_bool	has_space_around_player_pos(t_map *map, int y, int x)
{
	return (map->map[y - 1][x] > 1 || map->map[y + 1][x - 1] > 1
					|| map->map[y][x - 1] > 1 || map->map[y][x + 1] > 1);
}
