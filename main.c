/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:20:26 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/05 17:26:50 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void prototype(t_frame *frame);
void check_leak(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	printf("sizeof %lu \n", sizeof(t_dda));
	t_image	mlx_image;
	t_frame	mlx_frame;
	
	initialize_data(&mlx_frame, argc, argv);
	ft_mlx_setup(&mlx_frame, &mlx_image);
	prototype(&mlx_frame);
	mlx_frame.draw = &cub3d;
	mlx_loop_hook(mlx_frame.mlx, ft_mlx_render, &mlx_frame);
	mlx_loop(mlx_frame.mlx);
}

void prototype(t_frame *frame)
{
	atexit(check_leak);
	t_map *map = &(frame->map);
	map->map_h = 14;
	map->map_w = 34;
	map->minimap_divider = SCREEN_WIDTH / MINIMAP_DIVIDER / map->map_w;
	if (SCREEN_HEIGTH / MINIMAP_DIVIDER / map->map_h > map->minimap_divider)
		map->minimap_divider = SCREEN_HEIGTH / MINIMAP_DIVIDER / frame->map.map_h;
	map->map = malloc(map->map_h * sizeof(int *));
	for (int i = 0; i < map->map_h; i++)
		(map->map)[i] = malloc(map->map_w * sizeof(int));
	int worldMap[14][34]=
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

	map->textures = malloc(4 * sizeof(t_texture*));
	t_texture **texture = map->textures;
	
	// xpm1
	texture[0] = malloc(1 * sizeof(t_texture));
	void* texture_mlx_image = mlx_xpm_file_to_image(frame->mlx,
		"doge.xpm", 
		&((texture[0])->width), &((texture[0])->height));
	t_image *image = malloc(1 * sizeof(t_image));
	texture[0]->image = image;
	image->img = texture_mlx_image;
	image->addr = mlx_get_data_addr(
		image->img, &image->bits_per_pixel, &image->line_length, &image->endian
	);
	// xpm2
	texture[1] = malloc(1 * sizeof(t_texture));
	void* texture_mlx_image_ = mlx_xpm_file_to_image(frame->mlx,
		"xpm.xpm", 
		&((texture[1])->width), &((texture[1])->height));
	image = malloc(1 * sizeof(t_image));
	texture[1]->image = image;
	image->img = texture_mlx_image_;
	image->addr = mlx_get_data_addr(
		image->img, &image->bits_per_pixel, &image->line_length, &image->endian
	);

	texture[2] = texture[1];
	texture[3] = texture[1];
	printf("1: %d x %d\n", texture[0]->width, texture[0] -> height);
	printf("2: %d x %d\n", texture[1]->width, texture[1] -> height);
	
	frame->player_dir.x = 1.0;
	frame->player_dir.y = 0.0;
	frame->player_pos.x = 3.0;
	frame->player_pos.y = 3.0;
	frame->camera_dir.x = 0.0;
	frame->camera_dir.y = 0.66;
}
