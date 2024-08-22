/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:11:06 by yechakim          #+#    #+#             */
/*   Updated: 2024/08/22 10:32:30 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

#define SPACE 2

void	validate_map(t_frame *frame, t_map *map);
void	prototype(t_frame *frame);
t_bool is_fullfilled(t_metadata *metadata);


int	get_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		throw_parse_error("Failed to open file\n");
	return (fd);
}


t_bool	fill_direction(t_metadata *info, t_dir dir, char *line)
{
	(void)line;
	int fd;

	while (line && *line == ' ')
		line++;
	if (is_ext(line, ".xpm") == FALSE)
		throw_parse_error("Invalid file extension\n");
	fd = open(line, O_RDONLY);
	if (fd < 0)
		throw_parse_error("File is not invalid\n");	
	if (info->dir[dir])
		throw_parse_error("Duplicated texture\n");
	info->dir[dir] = ft_strdup(line);
	close(fd);
	return (TRUE);
}

t_bool	try_fill_direction(t_metadata *info, char *line)
{
	int i; 
	const char *dir_keys[5] = {NORTH, SOUTH, WEST, EAST, NULL};

	i = 0; 
	while (dir_keys[i])
	{
		if (ft_strncmp(dir_keys[i], line, DIR_KEY_LEN) == 0)
		{
			if (info->dir[i] != NULL)
				throw_parse_error("Duplicated Texture\n");
			fill_direction(info, i, line + DIR_KEY_LEN);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool valid_color_format(char *colors)
{
	char	*temp;
	int		color_amount;

	temp = colors;
	color_amount = 0;
	while (temp && *temp)
	{
		while (temp && *temp == ' ')
			temp++;
		if (!temp)
			throw_parse_error("Invalid color format with space\n");
		if(ft_isdigit(*temp) == FALSE)
			throw_parse_error("Invalid color format with digit\n");
		color_amount++;
		while (temp && ft_isdigit(*temp) == TRUE)
			temp++;
		if (color_amount != 3 && !temp)
			throw_parse_error("Invalid color format with amount color_amount\n");
		if (temp && *temp != ',' && color_amount != 3)
		{
			throw_parse_error("Invalid color format with ','\n");
		}
		printf("temp: %s\n", temp);
		if (temp && *temp)
			temp++;
	}
	if (color_amount != 3)
		throw_parse_error("Invalid color format\n");
	return (TRUE);
}



void fill_color(t_metadata *info, int key, char *colors)
{
	int			color_cnt;
	int			color;
	int			current_color;
	const int	rgb[3] = {16, 8, 0};

	color_cnt = 0;
	color = 0;
	printf("colors: %s\n", colors);
	if (valid_color_format(colors) == FALSE)
		throw_parse_error("Invalid color format\n");
	while (colors && color_cnt < 3)
	{
		while (colors && *colors == ' ')
			colors++;
		current_color = ft_atoi(colors);
		if (!(0 <= current_color && current_color <= 255))
			throw_parse_error("Invalid color value range\n");
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
	int		i;

	i = 0;
	while (color_keys[i])
	{
		if (ft_strncmp(color_keys[i], line, COLOR_KEY_LEN) == 0)
		{
			fill_color(info, i, line + COLOR_KEY_LEN);
			printf("color: %d\n", info->colors[i]);
			return (TRUE);
		}
		i++;
	}
	printf("fill color failed with line: %s\n", line);
	return (FALSE);
}

t_bool	parse_metadata(t_metadata *info, char *line)
{
	t_bool ret = FALSE;

	if (try_fill_direction(info, line) || try_fill_color(info, line))
		ret = TRUE;
	return (ret);
}

void dbg_metadata(t_metadata *metadata)
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
	char *line;
	char *trimedline;

	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			return (FALSE);
		trimedline = ft_strtrim(line, " \n");
		printf("line: %s\n", line);
		printf("trimedline: %s\n", trimedline);
		free(line);
		if (!trimedline)
			throw_parse_error("Failed to allocate memory\n");
		if (*trimedline == '\0')
		{
			free(trimedline);
			continue ;
		}
		if (ft_isdigit(trimedline[0])
			|| ft_strchr("NSWEFC", trimedline[0]) == NULL)
			return (FALSE);
		if (parse_metadata(metadata, trimedline) == FALSE)
		{
			printf("here\n");
			return (FALSE);
		}
		free(trimedline);
		dbg_metadata(metadata);
		if (is_fullfilled(metadata))
			return (TRUE);
	}
	return (TRUE);
}

char	*read_map_lines(int file)
{
	char	*line;
	char	*map_str;
	char	*temp;

	map_str = NULL;
	while (TRUE)
	{
		line = get_next_line(file);
		if (!line)
			break ;
		if (!map_str)
			map_str = ft_strdup(line);
		else
		{
			temp = ft_strjoin(map_str, line);
			free(map_str);
			map_str = temp;
		}
		free(line);
	}
	return (map_str);
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void fill_mapsize(t_map *map, char **lines)
{
	int i = 0;

	map->map_w = 0;
	while (lines[i])
	{
		map->map_w = ft_max(map->map_w, ft_strlen(lines[i]));
		i++;
	}
	map->map_h = i;
}

void fill_map(t_frame *frame, t_map *map, char **lines)
{
	int y_idx;
	int x_idx;
	int line_len;

	y_idx = 0;
	while (lines[y_idx])
	{
		printf("line: %s\n", lines[y_idx]);
		map->map[y_idx] = malloc(map->map_w * sizeof(int));
		if (!map->map[y_idx])
			throw_parse_error("Failed to allocate memory\n");
		ft_memset(map->map[y_idx], -1, map->map_w * sizeof(int));
		x_idx = 0;
		line_len = ft_strlen(lines[y_idx]);
		while (x_idx < line_len)
		{
			if (lines[y_idx][x_idx] == ' ')
				map->map[y_idx][x_idx] = SPACE;
			else if (ft_strchr("01", lines[y_idx][x_idx]))
				map->map[y_idx][x_idx] = lines[y_idx][x_idx] - '0';
			else if (ft_strchr("NSWE", lines[y_idx][x_idx]) != NULL)
			{
				printf("dir: %c\n", lines[y_idx][x_idx]);
				map->map[y_idx][x_idx] = 0;
				frame->player_pos.x = x_idx;
				frame->player_pos.y = y_idx;
				const char *dir = "NSWE";
				const int start_dir = 90 * (ft_strchr(dir, lines[y_idx][x_idx]) - dir + 1);
				frame->player_pos.x = x_idx;
				frame->player_pos.y = y_idx;
				frame->player_dir.x = cos(M_PI / 180.0 * start_dir);
				frame->player_dir.y = -sin(M_PI / 180.0 * start_dir);
				
				printf("fill_map. player_pos: %f %f\n", frame->player_pos.x, frame->player_pos.y);
				printf("fill_map. player_dir: %f %f\n", frame->player_dir.x, frame->player_dir.y);
			}
			else
				throw_parse_error("Invalid map character\n");
			x_idx++;
		}
		while(x_idx < map->map_w)
		{
			map->map[y_idx][x_idx] = SPACE;
			x_idx++;
		}
		y_idx++;
	}
}

void	validate_map(t_frame *frame, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->map_h)
	{
		j = 0;
		while (j < map->map_w)
		{
			if (map->map[i][j] == 0 && (i == 0 || i == map->map_h - 1 || j == 0 || j == map->map_w -1))
			{
				printf("pos: %d %d\n", i, j);
				throw_parse_error("Invalid map: Not surrounded by walls with endpoints\n");
			}
			if (map->map[i][j] == 0 && (map->map[i - 1][j] > 1 || map->map[i + 1][j] > 1 || map->map[i][j - 1] > 1 || map->map[i][j + 1] > 1))
			{
				printf("pos: %d %d up:%d, left: %d, right: %d, down: %d\n", i, j, map->map[i - 1][j], map->map[i][j - 1], map->map[i][j + 1], map->map[i + 1][j]);
				throw_parse_error("Invalid map: Not surrounded by walls with inner pos\n");
			}
			if (i == frame->player_pos.y && j == frame->player_pos.x && (i == 0 || i == map->map_h - 1 || j == 0 || j == map->map_w -1))
			{
				printf("pos: %d %d\n", i, j);
				throw_parse_error("Invalid map: Player Position is not surrounded by walls 1\n");
			}
			if (i == frame->player_pos.y && j == frame->player_pos.x && (map->map[i - 1][j] > 1 || map->map[i + 1][j - 1] > 1 || map->map[i][j - 1] > 1 || map->map[i][j + 1] > 1))
			{
				printf("pos: %d %d\n", i, j);
				throw_parse_error("Invalid map: Player Position is not surrounded by walls 2\n");
			}
			j++;
		}
		i++;
	}

}

t_bool	read_map(t_frame *frame, t_map *map, int file)
{
	char *map_str;
	char **lines;
	int line_idx;

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

void dbg_map(t_map *map)
{
	int i;
	int j;

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


void	initialize_data(t_frame *frame, int argc, char **argv)
{
	t_metadata *metadata;
	int file_descripter;
	if (!has_only_one_cub3d_file(argc, argv))
		exit(1);
	file_descripter = get_file(argv[1]);
	metadata = ft_calloc(1, sizeof(t_metadata));
	if (!metadata)
		throw_parse_error("Failed to allocate memory\n");
	if(!read_metadata(metadata, file_descripter))
		throw_parse_error("Failed to read metadata\n");
	if (!read_map(frame, &frame->map, file_descripter))
		throw_parse_error("Failed to read map\n");
	
	t_texture *texture_doge = cub3d_texture_create(frame, metadata->dir[DIR_N]);
	printf("---->> doge %p: t_h %d t_w %d\n",
		texture_doge, texture_doge->height, texture_doge->width);
	t_texture *texture_grid = cub3d_texture_create(frame, metadata->dir[DIR_E]);
	printf("---->> grid %p: t_h %d t_w %d\n",
		texture_grid, texture_grid->height, texture_grid->width);
	t_texture *texture_42 = cub3d_texture_create(frame, metadata->dir[DIR_W]);
	printf("---->> 42 %p: t_h %d t_w %d\n",
		texture_42, texture_42->height, texture_42->width);

	frame->map.textures[DIR_N] = cub3d_texture_create(frame, metadata->dir[DIR_N]);
	frame->map.textures[DIR_E] = cub3d_texture_create(frame, metadata->dir[DIR_E]);
	frame->map.textures[DIR_W] = cub3d_texture_create(frame, metadata->dir[DIR_W]);
	frame->map.textures[DIR_S] = cub3d_texture_create(frame, metadata->dir[DIR_S]);

	# define START_DIR 90
	// frame->player_dir.x = cos(M_PI / 180.0 * START_DIR);
	// frame->player_dir.y = -sin(M_PI / 180.0 * START_DIR);
	frame->camera_plane.x = POV * sin(M_PI / 180.0 * START_DIR);
	frame->camera_plane.y = POV * cos(M_PI / 180.0 * START_DIR);

	// frame->player_pos.x = 3;
	// frame->player_pos.y = 3;

	dbg_map(&frame->map);
	// map = &(frame->map);	
	// TODO: need to implement
	// if(!read_map(map, argv[1], file))
	// 	throw_parse_error("Failed to read map\n");
	// set_texture(metadata, map);
	// set_color(metadata, map);
}


void prototype(t_frame *frame)
{
	t_map *map = &(frame->map);
	map->map_h = 14;
	map->map_w = 33;
	map->map = malloc(map->map_h * sizeof(int *));
	for (int i = 0; i < map->map_h; i++)
		(map->map)[i] = malloc(map->map_w * sizeof(int));
	int worldMap[14][33]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	for (int y = 0; y < map->map_h; y++)
	{
		for (int x = 0; x < map->map_w; x++)
		{
			map->map[y][x] = worldMap[y][x];
		}
	}

	// t_texture **texture = map->textures;
	
	// // xpm1
	// texture[0] = malloc(1 * sizeof(t_texture));
	// void* texture_mlx_image = mlx_xpm_file_to_image(frame->mlx,
	// 	"doge.xpm", 
	// 	&((texture[0])->width), &((texture[0])->height));
	// t_image *image = malloc(1 * sizeof(t_image));
	// texture[0]->image = image;
	// image->img = texture_mlx_image;
	// image->addr = mlx_get_data_addr(
	// 	image->img, &image->bits_per_pixel, &image->line_length, &image->endian
	// );
	// // xpm2
	// texture[1] = malloc(1 * sizeof(t_texture));
	// void* texture_mlx_image_ = mlx_xpm_file_to_image(frame->mlx,
	// 	"xpm.xpm", 
	// 	&((texture[1])->width), &((texture[1])->height));
	// image = malloc(1 * sizeof(t_image));
	// texture[1]->image = image;
	// image->img = texture_mlx_image_;
	// image->addr = mlx_get_data_addr(
	// 	image->img, &image->bits_per_pixel, &image->line_length, &image->endian
	// );

	// texture[2] = texture[1];
	// texture[3] = texture[1];
	// printf("1: %d x %d\n", texture[0]->width, texture[0] -> height);
	// printf("2: %d x %d\n", texture[1]->width, texture[1] -> height);
	
	t_texture *texture_doge = cub3d_texture_create(frame, "doge.xpm");
	printf("---->> doge %p: t_h %d t_w %d\n",
		texture_doge, texture_doge->height, texture_doge->width);
	t_texture *texture_grid = cub3d_texture_create(frame, "grid.xpm");
	printf("---->> grid %p: t_h %d t_w %d\n",
		texture_grid, texture_grid->height, texture_grid->width);
	t_texture *texture_42 = cub3d_texture_create(frame, "42.xpm");
	printf("---->> 42 %p: t_h %d t_w %d\n",
		texture_42, texture_42->height, texture_42->width);
	map->textures[DIR_N] = texture_doge;
	map->textures[DIR_E] = texture_grid;
	map->textures[DIR_W] = texture_42;
	map->textures[DIR_S] = texture_doge;

	# define START_DIR 90
	frame->player_dir.x = cos(M_PI / 180.0 * START_DIR);
	frame->player_dir.y = -sin(M_PI / 180.0 * START_DIR);
	frame->camera_plane.x = POV * sin(M_PI / 180.0 * START_DIR);
	frame->camera_plane.y = POV * cos(M_PI / 180.0 * START_DIR);

	frame->player_pos.x = 3;
	frame->player_pos.y = 3;
}


t_bool is_fullfilled(t_metadata *metadata)
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
