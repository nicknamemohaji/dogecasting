/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:39:06 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/28 08:12:34 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

void	fill_map(t_frame *frame, t_map *map, char **lines);
void	fill_coordinate(t_frame *frame,
			t_map *map, char **lines, t_vector2i pos);
void	fill_player_pos(t_frame *frame, int x, int y, int start_dir);

void	fill_map(t_frame *frame, t_map *map, char **lines)
{
	int			y_idx;
	int			x_idx;
	int			line_len;

	y_idx = 0;
	frame->player_pos.x = -1;
	frame->player_pos.y = -1;
	while (lines[y_idx])
	{
		map->map[y_idx] = malloc(map->map_w * sizeof(int));
		if (!map->map[y_idx])
			throw_parse_error(NULL);
		ft_memset(map->map[y_idx], -1, map->map_w * sizeof(int));
		x_idx = 0;
		line_len = ft_strlen(lines[y_idx]);
		while (x_idx < line_len)
			fill_coordinate(frame, map, lines, (t_vector2i){x_idx++, y_idx});
		while (x_idx < map->map_w)
			map->map[y_idx][x_idx++] = SPACE;
		y_idx++;
	}
}

void	fill_coordinate(t_frame *frame,
			t_map *map, char **lines, t_vector2i pos)
{
	const char	*dir = "NWSE";
	int			start_dir;

	if (lines[pos.y][pos.x] == ' ')
		map->map[pos.y][pos.x] = SPACE;
	else if (ft_strchr("01", lines[pos.y][pos.x]))
		map->map[pos.y][pos.x] = lines[pos.y][pos.x] - '0';
	else if (ft_strchr(dir, lines[pos.y][pos.x]) != NULL)
	{
		map->map[pos.y][pos.x] = 0;
		start_dir = 90 * (ft_strchr(dir, lines[pos.y][pos.x]) - dir + 1);
		fill_player_pos(frame, pos.x, pos.y, start_dir);
	}
	else
		throw_parse_error(ERR_MAP ERR_MAP_CHAR);
}

void	fill_player_pos(t_frame *frame, int x, int y, int start_dir)
{
	static int	player_count = 0;

	if (player_count > 0)
		throw_parse_error(ERR_MAP ERR_MAP_DUP_PLAYER);
	frame->player_pos.x = x + 0.5;
	frame->player_pos.y = y + 0.5;
	frame->player_dir.x = cos(M_PI / 180.0 * start_dir);
	frame->player_dir.y = -sin(M_PI / 180.0 * start_dir);
	frame->camera_plane.x = POV * sin(M_PI / 180.0 * start_dir);
	frame->camera_plane.y = POV * cos(M_PI / 180.0 * start_dir);
	player_count++;
}
