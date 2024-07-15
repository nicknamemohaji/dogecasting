/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:11:06 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/15 21:13:47 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

void	prototype(t_frame *frame);

int	get_file(char *filename)
{
	int fd;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		throw_parse_error("Failed to open file\n");
	return (fd);
}


t_bool	fill_direction(t_metadata *info, const char *dir_key, char *line)
{
	(void)line;
	if (ft_strncmp(dir_key, NORTH, DIR_KEY_LEN) == 0)
	{
		info->north = ft_strdup(line);
	}
	else if(ft_strncmp(dir_key, SOUTH, DIR_KEY_LEN) == 0)
	{
		info->south = ft_strdup(line);
	}
	else if(ft_strncmp(dir_key, WEST, DIR_KEY_LEN) == 0)
	{
		info->west = ft_strdup(line);
	}
	else if(ft_strncmp(dir_key, EAST, DIR_KEY_LEN) == 0)
	{
		info->east = ft_strdup(line);
	}
	else
	{
		return (FALSE);
	}
	return (TRUE);
}

t_bool	try_fill_direction(t_metadata *info, char *line)
{
	int i; 
	const char *dir_keys[5] = {NORTH, SOUTH, WEST, EAST, NULL};
	// char *filename = NULL;
	i = 0; 
	while(dir_keys[i]){
		if(ft_strncmp(*dir_keys, line, DIR_KEY_LEN) == 0){
			fill_direction(info, *dir_keys, line + DIR_KEY_LEN);
		}
		i++;
	}
	// TODO: need to implement
	return (FALSE);
}

t_bool	try_fill_color(t_metadata *info, char *line)
{
	// char *color_keys = {FLOOR_COLOR, CEILING_COLOR, NULL};
	// TODO: need to implement
	(void)info;
	(void)line;
	return (FALSE);
}

t_bool	parse_metadata(t_metadata *info, char *line)
{
	t_bool ret = FALSE;

	if (try_fill_direction(info, line) || try_fill_color(info, line))
		ret = TRUE;
	return (FALSE);
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
		trimedline = ft_strtrim(line, " ");
		free(line);
		if (!trimedline)
			throw_parse_error("Failed to allocate memory\n");
		if (ft_isdigit(trimedline[0]) || ft_strchr("NSWEFC", trimedline[0]) == NULL)
			return (FALSE);
		if (parse_metadata(metadata, trimedline) == FALSE)
			return (FALSE);
		free(trimedline);
		// if (is_fullfilled(metadata) == TRUE)
			// return (TRUE);
	}
	return (TRUE);
}

void	initialize_data(t_frame *frame, int argc, char **argv)
{
	// t_map		*map;
	// t_metadata *metadata;
	// int			file;
	(void)argc;	
	(void)argv;
	(void)frame;
	#ifndef PARSER
	 return (prototype(frame));
	#else
	
	return (exit(20));
	if (!has_only_one_cub3d_file(argc, argv))
		exit(1);
	int file_descripter = get_file(argv[1]);
	t_metadata *metadata = ft_calloc(1, sizeof(t_metadata));
	if (!metadata)
		throw_parse_error("Failed to allocate memory\n");
	if(!read_metadata(metadata, file_descripter))
		throw_parse_error("Failed to read metadata\n");
	// TODO: need to implement
	// if(!read_map(map, argv[1], file))
	// 	throw_parse_error("Failed to read map\n");
	// set_texture(metadata, map);
	// set_color(metadata, map);
	#endif
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