/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:20:26 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/20 13:58:35 by kyungjle         ###   ########.fr       */
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
	t_image	mlx_image;
	t_frame	mlx_frame;

	ft_mlx_setup(&mlx_frame, &mlx_image);
	prototype(&mlx_frame);
	mlx_frame.draw = &cub3d;
	ft_mlx_render(&mlx_frame);
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
	printf("---->> doge %p: t_h %d t_w %d\n", texture_doge, texture_doge->height, texture_doge->width);
	t_texture *texture_grid = cub3d_texture_create(frame, "grid.xpm");
	printf("---->> grid %p: t_h %d t_w %d\n", texture_grid, texture_grid->height, texture_grid->width);
	t_texture *texture_42 = cub3d_texture_create(frame, "42.xpm");
	printf("---->> 42 %p: t_h %d t_w %d\n", texture_42, texture_42->height, texture_42->width);
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
