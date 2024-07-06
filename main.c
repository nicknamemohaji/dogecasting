/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:20:26 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/07 01:34:23 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void prototype(t_frame *frame);
void check_leak(void)
{
	system("leaks cub3D");
}

int	main(void)
{
	printf("sizeof %lu \n", sizeof(t_dda));
	t_image	mlx_image;
	t_frame	mlx_frame;

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

	map->textures = malloc(4 * sizeof(t_texture*));
	t_texture* texture[4];
	
	// // xpm1: doge
	// texture[0] = malloc(1 * sizeof(t_texture));
	// {
	// 	void* texture_mlx_image = mlx_xpm_file_to_image(frame->mlx,
	// 		"doge.xpm", 
	// 		&((texture[0])->width), &((texture[0])->height));
	// 	t_image *image = malloc(1 * sizeof(t_image));
	// 	texture[0]->image = image;
	// 	image->img = texture_mlx_image;
	// 	image->addr = mlx_get_data_addr(
	// 		image->img, &image->bits_per_pixel, &image->line_length, &image->endian
	// 	);
	// }
	// xpm2: grid
	texture[1] = malloc(1 * sizeof(t_texture));
	{
		void* texture_mlx_image = mlx_xpm_file_to_image(frame->mlx,
			"xpm.xpm", 
			&((texture[1])->width), &((texture[1])->height));
		t_image *image = malloc(1 * sizeof(t_image));
		texture[1]->image = image;
		image->img = texture_mlx_image;
		image->addr = mlx_get_data_addr(
			image->img, &image->bits_per_pixel, &image->line_length, &image->endian
		);
	}

	// xpm3: 42
	texture[2] = malloc(1 * sizeof(t_texture));
	{
		void* texture_mlx_image = mlx_xpm_file_to_image(frame->mlx,
			"42.xpm", 
			&((texture[2])->width), &((texture[2])->height));
		t_image *image = malloc(1 * sizeof(t_image));
		texture[2]->image = image;
		image->img = texture_mlx_image;
		image->addr = mlx_get_data_addr(
			image->img, &image->bits_per_pixel, &image->line_length, &image->endian
		);
	}
	map->textures[DIR_N] = texture[2];
	map->textures[DIR_S] = texture[2];
	map->textures[DIR_E] = texture[2];
	map->textures[DIR_W] = texture[2];
	printf("height %d width %d\n", texture[2]->height, texture[2]->width);
	frame->player_pos.x = 3.0;
	frame->player_pos.y = 3.0;
	# define START_DIR 90
	frame->player_dir.x = cos(M_PI / 180.0 * START_DIR);
	frame->player_dir.y = -sin(M_PI / 180.0 * START_DIR);
	frame->camera_plane.x = POV * sin(M_PI / 180.0 * START_DIR);
	frame->camera_plane.y = POV * cos(M_PI / 180.0 * START_DIR);
}
