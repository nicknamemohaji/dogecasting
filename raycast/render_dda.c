/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 01:51:03 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/04 03:51:13 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				cub3d_render(t_frame *frame, const t_map *map,
						const t_vector2d player_pos,
						const t_vector2d player_dir);
static void			calc_dda_param(t_dda *dda, const int x,
						const t_vector2d player, const t_vector2d camera);
static void			calc_dda_param2(t_dda *dda, const t_vector2d player_pos);
static t_vector2i	calc_hit(t_dda *dda, const t_map *map, t_vector2i map_pos);
static void			prepare_render_params(t_render_params *params,
						t_vector2d player_pos);

void	cub3d_render(t_frame *frame, const t_map *map,
			const t_vector2d player_pos, const t_vector2d player_dir)
{
	t_vector2i			map_pos;
	t_render_params		render_param;
	int					x;
	static const float	screen_ratio = (float) SCREEN_WIDTH
		/ (float) SCREEN_HEIGTH;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		map_pos.x = (int) player_pos.x;
		map_pos.y = (int) player_pos.y;
		calc_dda_param(&(frame->dda[x]), x, player_dir, frame->camera_dir);
		calc_dda_param2(&(frame->dda[x]), player_pos);
		map_pos = calc_hit(&(frame->dda[x]), map, map_pos);
		render_param.dda_result = frame->dda[x];
		if ((frame->dda[x]).dist_plane == 0)
			(frame->dda[x]).dist_plane = 1;
		render_param.line_height = (int)(SCREEN_HEIGTH * screen_ratio
				/ (frame->dda[x]).dist_plane);
		render_param.texture = map->textures[render_param.dda_result.side];
		render_param.x = x;
		prepare_render_params(&render_param, player_pos);
		cub3d_render_draw(frame, &render_param);
		cub3d_minimap_ray(frame, &(frame->dda[x]), map_pos, player_pos);
	}
}

static void	calc_dda_param(t_dda *dda, const int x,
					const t_vector2d player_dir, const t_vector2d camera_dir)
{
	const t_vector2d	camera = ft_vector2d_mul(camera_dir,
			(2.0 * x) / (double) SCREEN_WIDTH - 1.0);

	dda->ray_dir = ft_vector2d_add(player_dir, camera);
	if (dda->ray_dir.x == 0)
		dda->dist_delta.x = 1e30;
	else
		dda->dist_delta.x = fabs(1.0 / dda->ray_dir.x);
	if (dda->ray_dir.y == 0)
		dda->dist_delta.y = 1e30;
	else
		dda->dist_delta.y = fabs(1.0 / dda->ray_dir.y);
	dda->dist_plane = 0.0;
	dda->side = -1;
}

static void	calc_dda_param2(t_dda *dda, const t_vector2d player_pos)
{
	if (dda->ray_dir.x < 0)
	{
		dda->step.x = -1;
		dda->dist.x = (player_pos.x - (int) player_pos.x) * dda->dist_delta.x;
	}
	else
	{
		dda->step.x = 1;
		dda->dist.x = ((int) player_pos.x + 1.0 - player_pos.x) \
			* dda->dist_delta.x;
	}
	if (dda->ray_dir.y < 0)
	{
		dda->step.y = -1;
		dda->dist.y = (player_pos.y - (int) player_pos.y) * dda->dist_delta.y;
	}
	else
	{
		dda->step.y = 1;
		dda->dist.y = ((int) player_pos.y + 1.0 - player_pos.y) \
			* dda->dist_delta.y;
	}
}

static t_vector2i	calc_hit(t_dda *dda, const t_map *map, t_vector2i map_pos)
{
	while (map->map[map_pos.y][map_pos.x] == 0)
	{
		if (dda->dist.x < dda->dist.y)
		{
			dda->dist.x += dda->dist_delta.x;
			map_pos.x += dda->step.x;
			dda->dist_plane = dda->dist.x - dda->dist_delta.x;
			if (dda->ray_dir.x < 0)
				dda->side = DIR_W;
			else
				dda->side = DIR_E;
		}
		else
		{
			dda->dist.y += dda->dist_delta.y;
			map_pos.y += dda->step.y;
			dda->dist_plane = dda->dist.y - dda->dist_delta.y;
			if (dda->ray_dir.y < 0)
				dda->side = DIR_N;
			else
				dda->side = DIR_S;
		}
	}
	return (map_pos);
}

static void	prepare_render_params(t_render_params *params,
				t_vector2d player_pos)
{
	const t_texture	*texture = params->texture;

	params->draw_start = (SCREEN_HEIGTH - params->line_height) / 2;
	params->draw_end = (SCREEN_HEIGTH + params->line_height) / 2;
	if (params->draw_start < 0)
		params->draw_start = 0;
	if (params->draw_end >= SCREEN_HEIGTH)
		params->draw_end = SCREEN_HEIGTH - 1;
	if (params->dda_result.side == DIR_N || params->dda_result.side == DIR_S)
		params->wall_pos = player_pos.x + params->dda_result.dist_plane
			* params->dda_result.ray_dir.x;
	else
		params->wall_pos = player_pos.y + params->dda_result.dist_plane
			* params->dda_result.ray_dir.y;
	params->wall_pos -= floor((params->wall_pos));
	params->step = ((float) texture->height) / ((float) params->line_height);
}
