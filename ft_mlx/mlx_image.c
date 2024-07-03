/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:26:10 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/04 08:13:58 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_mlx_image_put(t_frame *frame, t_vector2i pos, int color);
unsigned int	ft_mlx_image_color(t_image *img, int x, int y);
int				ft_mlx_render(t_frame *frame);

void	ft_mlx_image_put(t_frame *frame, t_vector2i pos, int color)
{
	t_image	*image;
	char	*dst;

	image = frame->image;
	dst = image->addr + (pos.y * image->line_length
			+ pos.x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	ft_mlx_image_color(t_image *img, int x, int y)
{
	char	*dst;

	// TODO 캐시 고려하면 한 텍스쳐 이미지에 대해 x축 스캐닝하는게 더 빠를 듯
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return ((*(unsigned int *)dst) & 0xffffff);
}

int	ft_mlx_render(t_frame *frame)
{
	mlx_clear_window(frame->mlx, frame->window);
	ft_mlx_setup_image(frame, frame->image);
	frame->draw(frame);
	mlx_put_image_to_window(frame->mlx, frame->window, frame->image->img, 0, 0);
	mlx_destroy_image(frame->mlx, frame->image->img);
	interface_fps_counter(frame);
	return (0);
}
