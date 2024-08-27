/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 07:08:07 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 14:17:42 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

void	render_background(t_frame *frame)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGTH / 2)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			ft_mlx_image_put(frame,
				(t_vector2i){x, y},
				0x00ffff);
			ft_mlx_image_put(frame,
				(t_vector2i){x, (SCREEN_HEIGTH - 1 - y)},
				0xffff00);
		}
	}
}
