/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:37:41 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/20 14:14:42 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

void	cub3d(t_frame *frame);

void	cub3d(t_frame *frame)
{
	const t_map			*map = &(frame->map);
	const t_vector2d	player_pos = frame->player_pos;
	const t_vector2d	player_dir = frame->player_dir;

	cub3d_render(frame, map, player_pos, player_dir);
	cub3d_interface(frame, map, player_pos);
}
