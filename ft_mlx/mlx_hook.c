/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:05:52 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/28 17:05:19 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

int			ft_mlx_destroy(t_frame *frame);
int			ft_mlx_event_key(int keycode, t_frame *frame);
static void	change_dir(t_frame *frame, double delta);
static void	change_pos(t_frame *frame, t_dir dir, double speed);

int	ft_mlx_destroy(t_frame *frame)
{
	int	i;

	mlx_destroy_window(frame->mlx, frame->window);
	i = -1;
	while (++i < frame->map.map_h)
		free(frame->map.map[i]);
	free(frame->map.map);
	i = -1;
	while (++i < 4)
	{
		free(frame->map.textures[i]->image);
		free(frame->map.textures[i]);
	}
	free(frame->dda);
	exit(0);
}

int	ft_mlx_event_key(int keycode, t_frame *frame)
{
	static const float	rotate_speed = M_PI / 72.0;

	if (keycode == KEYBOARD_ESC)
		ft_mlx_destroy(frame);
	if (keycode == KEYBOARD_A)
		change_pos(frame, DIR_W, -MOVE_SPEED);
	else if (keycode == KEYBOARD_D)
		change_pos(frame, DIR_E, MOVE_SPEED);
	else if (keycode == KEYBOARD_W)
		change_pos(frame, DIR_N, MOVE_SPEED);
	else if (keycode == KEYBOARD_S)
		change_pos(frame, DIR_S, -MOVE_SPEED);
	else if (keycode == KEYBOARD_LEFT)
		change_dir(frame, -rotate_speed);
	else if (keycode == KEYBOARD_RIGHT)
		change_dir(frame, rotate_speed);
	return (0);
}

static void	change_dir(t_frame *frame, double delta)
{
	frame->player_dir = ft_vector2d_rotate(frame->player_dir, delta);
	frame->camera_plane = ft_vector2d_rotate(frame->camera_plane, delta);
	frame->event = TRUE;
}

static void	change_pos(t_frame *frame, t_dir dir, double speed)
{
	int					**map;
	t_vector2d			new_pos;
	t_vector2d			direction_vector;
	static const float	degree_90 = M_PI / 2.0f;

	direction_vector = ft_vector2d_mul(frame->player_dir, speed);
	if (dir == DIR_E || dir == DIR_W)
		direction_vector = ft_vector2d_rotate(direction_vector, degree_90);
	new_pos = ft_vector2d_add(frame->player_pos, direction_vector);
	map = frame->map.map;
	if (map[(int)new_pos.y][(int)new_pos.x] != 0
		|| map[(int)(new_pos.y + MOVE_MAX)][(int)new_pos.x] != 0
		|| map[(int)(new_pos.y - MOVE_MAX)][(int)new_pos.x] != 0
		|| map[(int)new_pos.y][(int)(new_pos.x + MOVE_MAX)] != 0
		|| map[(int)new_pos.y][(int)(new_pos.x - MOVE_MAX)] != 0)
		new_pos = frame->player_pos;
	frame->player_pos = new_pos;
	frame->event = TRUE;
}
