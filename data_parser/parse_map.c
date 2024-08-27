/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:32:38 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 15:39:57 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

t_bool	read_map(t_frame *frame, t_map *map, int file);

t_bool	read_map(t_frame *frame, t_map *map, int file)
{
	char	*map_str;
	char	**lines;
	int		line_idx;

	line_idx = 0;
	map_str = read_map_lines(file);
	if (!map_str)
		return (FALSE);
	lines = ft_split(map_str, '\n');
	if (!lines)
		throw_parse_error(NULL);
	free(map_str);
	fill_mapsize(map, lines);
	map->map = malloc(map->map_h * sizeof(int *));
	if (!map->map)
		throw_parse_error(NULL);
	fill_map(frame, map, lines);
	ft_free_strs(lines);
	if (frame->player_pos.x == -1 || frame->player_pos.y == -1)
		throw_parse_error(ERR_MAP ERR_MAP_NO_PLAYER);
	validate_map(frame, map);
	return (TRUE);
}
