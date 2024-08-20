/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 07:13:31 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/20 14:14:42 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"
// include uint64_t
#include <stdint.h>

void	ft_mlx_draw_rectangle(t_frame *frame, const unsigned int size,
			const unsigned int color, const t_vector2i screen_pos);

void	ft_mlx_draw_rectangle(t_frame *frame, const unsigned int size,
			const unsigned int color, const t_vector2i screen_pos)
{
	unsigned int	x;
	unsigned int	y;
	t_image const	*image = frame->image;
	char			*dst;

	y = -1;
	while (++y < size)
	{
		x = 0;
		while (x < size)
		{
			dst = image->addr + ((screen_pos.y + y) * image->line_length)
				+ (screen_pos.x + x) * (image->bits_per_pixel / 8);
			*(uint64_t *)dst = ((uint64_t)(color & 0xffffff) << 32) + color;
			x += 2;
		}
	}
}
