/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:26:10 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/20 13:54:52 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_image_put(t_frame *frame, t_vector2i pos, int color);
int		ft_mlx_render(t_frame *frame);

void	ft_mlx_image_put(t_frame *frame, t_vector2i pos, int color)
{
	t_image	*image;
	char	*dst;

	image = frame->image;
	dst = image->addr + (pos.y * image->line_length
			+ pos.x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_mlx_render(t_frame *frame)
{
	mlx_clear_window(frame->mlx, frame->window);
	ft_mlx_setup_image(frame);
	frame->draw(frame);
	mlx_put_image_to_window(frame->mlx, frame->window, frame->image->img, 0, 0);
	mlx_destroy_image(frame->mlx, frame->image->img);
	return (0);
}
