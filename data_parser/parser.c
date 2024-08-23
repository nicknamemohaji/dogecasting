/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:11:06 by yechakim          #+#    #+#             */
/*   Updated: 2024/08/23 12:52:45 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parser.h"
#include "get_next_line.h"

#define SPACE 2

void	validate_map(t_frame *frame, t_map *map);
t_bool	is_fullfilled(t_metadata *metadata);

int	get_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		throw_parse_error("Failed to open file\n");
	return (fd);
}

t_bool	fill_direction(t_metadata *info, t_dir dir, char *line)
{
	int	fd;

	while (line && *line == ' ')
		line++;
	if (is_ext(line, VALID_TEXTURE_EXT) == FALSE)
		throw_parse_error("Invalid file extension\n");
	fd = open(line, O_RDONLY);
	if (fd < 0)
	{
		printf("err in open\n");
		throw_parse_error(NULL);
	}
	if (info->dir[dir])
		throw_parse_error(ERR_DUPLICATE_METADATA);
	info->dir[dir] = ft_strdup(line);
	close(fd);
	return (TRUE);
}

t_bool	try_fill_direction(t_metadata *info, char *line)
{
	const char	*dir_keys[5] = {NORTH, SOUTH, WEST, EAST, NULL};
	int			i;

	i = 0;
	while (dir_keys[i])
	{
		if (ft_strncmp(dir_keys[i], line, DIR_KEY_LEN) == 0)
		{
			if (info->dir[i] != NULL)
				throw_parse_error(ERR_DUPLICATE_METADATA);
			fill_direction(info, i, line + DIR_KEY_LEN);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	valid_color_format(char *colors)
{
	int		color_amount;

	color_amount = 0;
	while (colors && *colors)
	{
		while (colors && *colors == ' ')
			colors++;
		if (!colors)
			throw_parse_error(ERR_COLOR_FORMAT);
		if (ft_isdigit(*colors) == FALSE)
			throw_parse_error(ERR_COLOR_CHAR);
		color_amount++;
		while (colors && ft_isdigit(*colors) == TRUE)
			colors++;
		if (color_amount != 3 && !colors)
			throw_parse_error(ERR_COLOR_FORMAT);
		if (colors && *colors != ',' && color_amount != 3)
			throw_parse_error(ERR_COLOR_FORMAT_WITH_DELIMITER);
		if (colors && *colors)
			colors++;
	}
	if (color_amount != 3)
		throw_parse_error(ERR_COLOR_FORMAT);
	return (TRUE);
}

void	fill_color(t_metadata *info, int key, char *colors)
{
	int			color_cnt;
	int			color;
	int			current_color;
	const int	rgb[3] = {16, 8, 0};

	color_cnt = 0;
	color = 0;
	printf("colors: %s\n", colors);
	if (valid_color_format(colors) == FALSE)
		throw_parse_error(ERR_COLOR_FORMAT);
	while (colors && color_cnt < 3)
	{
		while (colors && *colors == ' ')
			colors++;
		current_color = ft_atoi(colors);
		if (!(0 <= current_color && current_color <= 255))
			throw_parse_error(ERR_COLOR_RANGE);
		info->colors[key] += current_color << rgb[color_cnt];
		color_cnt++;
		colors = ft_strchr(colors, ',');
		if (colors)
			colors++;
	}
}

t_bool	try_fill_color(t_metadata *info, char *line)
{
	const char	*color_keys[3] = {FLOOR_COLOR, CEILING_COLOR, NULL};
	int			i;

	i = 0;
	while (color_keys[i])
	{
		if (ft_strncmp(color_keys[i], line, COLOR_KEY_LEN) == 0)
			return (fill_color(info, i, line + COLOR_KEY_LEN), TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	parse_metadata(t_metadata *info, char *line)
{
	return (try_fill_direction(info, line) || try_fill_color(info, line));
}

void	dbg_metadata(t_metadata *metadata)
{
	printf("NORTH: %s\n", metadata->dir[DIR_N]);
	printf("SOUTH: %s\n", metadata->dir[DIR_S]);
	printf("WEST: %s\n", metadata->dir[DIR_W]);
	printf("EAST: %s\n", metadata->dir[DIR_E]);
	printf("FLOOR: %d\n", metadata->colors[FLOOR]);
	printf("CEILING: %d\n", metadata->colors[CEILING]);
}

t_bool	read_metadata(t_metadata *metadata, int fd)
{
	char	*line;
	char	*trimedline;

	while (TRUE)
	{
		errno = 0;
		line = get_next_line(fd);
		if (errno != 0)
		{
			printf("err in get_next_line\n");
			throw_parse_error(NULL);
		}
		if (!line)
			return (FALSE);
		trimedline = ft_strtrim(line, " \n");
		free(line);
		if (!trimedline)
			throw_parse_error(NULL);
		if (*trimedline != '\0')
		{
			if (ft_strchr("NSWEFC", trimedline[0]) == NULL)
				return (FALSE);
			if (parse_metadata(metadata, trimedline) == FALSE)
				return (FALSE);
		}
		free(trimedline);
		if (is_fullfilled(metadata))
			return (TRUE);
	}
	return (TRUE);
}

char	*read_map_lines(int file)
{
	char	*line;
	char	*map_str;

	line = get_next_line(file);
	map_str = ft_strdup(line);
	while (TRUE && map_str)
	{
		if (errno != 0)
			throw_parse_error(NULL);
		if (!line)
			break ;
		if (*line == '\n')
		{
			free(line);
			line = ft_strdup(" \n");
			if (!line)
				throw_parse_error(NULL);
		}
		map_str = ft_strjoin_and_free(map_str, line, FREE_S1);
		if (!map_str)
			throw_parse_error(NULL);
		free(line);
		line = get_next_line(file);
	}
	return (map_str);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	fill_mapsize(t_map *map, char **lines)
{
	int	i;

	i = 0;
	map->map_w = 0;
	while (lines[i])
	{
		map->map_w = ft_max(map->map_w, ft_strlen(lines[i]));
		i++;
	}
	map->map_h = i;
}

void	fill_player_pos(t_frame *frame, int x, int y, int start_dir)
{
	frame->player_pos.x = x + 0.5;
	frame->player_pos.y = y + 0.5;
	frame->player_dir.x = cos(M_PI / 180.0 * start_dir);
	frame->player_dir.y = -sin(M_PI / 180.0 * start_dir);
	frame->camera_plane.x = POV * sin(M_PI / 180.0 * start_dir);
	frame->camera_plane.y = POV * cos(M_PI / 180.0 * start_dir);
}

void	fill_coordinate(t_frame *frame,
	t_map *map, char **lines, t_vector2i pos)
{
	const char	*dir = "NSWE";
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
		throw_parse_error("Invalid map character\n");
}

void	fill_map(t_frame *frame, t_map *map, char **lines)
{
	int			y_idx;
	int			x_idx;
	int			line_len;

	y_idx = 0;
	while (lines[y_idx])
	{
		map->map[y_idx] = malloc(map->map_w * sizeof(int));
		if (!map->map[y_idx])
			throw_parse_error(NULL);
		ft_memset(map->map[y_idx], -1, map->map_w * sizeof(int));
		x_idx = 0;
		line_len = ft_strlen(lines[y_idx]);
		while (x_idx < line_len)
		{
			fill_coordinate(frame, map, lines, (t_vector2i){x_idx, y_idx});
			x_idx++;
		}
		while (x_idx < map->map_w)
		{
			map->map[y_idx][x_idx] = SPACE;
			x_idx++;
		}
		y_idx++;
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

t_bool	has_space_around_player_pos(t_map *map, int y, int x)
{
	return (map->map[y - 1][x] > 1 || map->map[y + 1][x - 1] > 1
					|| map->map[y][x - 1] > 1 || map->map[y][x + 1] > 1);
}

t_bool	player_pos_in_outline(t_map *map, t_vector2i pos, t_vector2i curr)
{
	return (curr.x == pos.x && curr.y == pos.y
		&& (pos.x == 0 || pos.x == map->map_w - 1
			|| pos.y == 0 || pos.y == map->map_h - 1));
}

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
			{
				throw_parse_error("Invalid map: \
				Player Position is not surrounded by walls 1\n");
			}
			if (i == frame->player_pos.y && j == frame->player_pos.x
				&& has_space_around_player_pos(map, i, j))
			{
				throw_parse_error("Invalid map: \
					Player Position is not surrounded by walls 2\n");
			}
			j++;
		}
		i++;
	}
}

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
		throw_parse_error("Failed to allocate memory\n");
	free(map_str);
	fill_mapsize(map, lines);
	map->map = malloc(map->map_h * sizeof(int *));
	if (!map->map)
		throw_parse_error("Failed to allocate memory\n");
	fill_map(frame, map, lines);
	ft_free_strs(lines);
	validate_map(frame, map);
	return (TRUE);
}

void	dbg_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	printf("map_h: %d\n", map->map_h);
	printf("map_w: %d\n", map->map_w);
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			printf("%d", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	set_textures(t_frame *frame, t_metadata *metadata)
{
	frame->map.textures[DIR_N]
		= cub3d_texture_create(frame, metadata->dir[DIR_N]);
	frame->map.textures[DIR_E]
		= cub3d_texture_create(frame, metadata->dir[DIR_E]);
	frame->map.textures[DIR_W]
		= cub3d_texture_create(frame, metadata->dir[DIR_W]);
	frame->map.textures[DIR_S]
		= cub3d_texture_create(frame, metadata->dir[DIR_S]);
}

void	initialize_data(t_frame *frame, int argc, char **argv)
{
	t_metadata	*metadata;
	int			file_descripter;

	if (!has_only_one_cub3d_file(argc, argv))
		exit(1);
	file_descripter = get_file(argv[1]);
	metadata = ft_calloc(1, sizeof(t_metadata));
	if (!metadata)
		throw_parse_error("Failed to allocate memory\n");
	if (!read_metadata(metadata, file_descripter))
		throw_parse_error("Failed to read metadata\n");
	if (!read_map(frame, &frame->map, file_descripter))
		throw_parse_error("Failed to read map\n");
	set_textures(frame, metadata);
	dbg_map(&frame->map);
}

t_bool	is_fullfilled(t_metadata *metadata)
{
	int	i;

	i = 0;
	while (i < DIR_KEY_LEN)
	{
		if (metadata->dir[i] == NULL)
			return (FALSE);
		i++;
	}
	if (!metadata->colors[CEILING] || !metadata->colors[FLOOR])
		return (FALSE);
	return (TRUE);
}
