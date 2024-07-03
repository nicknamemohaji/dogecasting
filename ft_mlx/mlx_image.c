/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:26:10 by kyungjle          #+#    #+#             */
/*   Updated: 2024/06/27 12:16:06 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_mlx_image_put(t_frame *frame, t_vector2i pos,
					int color, int level);
unsigned int	ft_mlx_image_color(t_image *img, int x, int y);
int				ft_mlx_render(t_frame *frame);

void	ft_mlx_image_put(t_frame *frame, t_vector2i pos, int color, int level)
{
	t_image	*image;
	char	*dst;

	image = frame->image;
	dst = image->addr +
		(pos.y * image->line_length + pos.x * (image->bits_per_pixel / 8));
	if (frame->screen[pos.x][pos.y] <= level)
	{
		*(unsigned int *)dst = color;
		frame->screen[pos.x][pos.y] = level;
	}
}

unsigned int	ft_mlx_image_color(t_image *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return ((*(unsigned int *)dst) & 0xffffff);
}

int	ft_mlx_render(t_frame *frame)
{
	int	x;
	int	y;

	mlx_clear_window(frame->mlx, frame->window);
	ft_mlx_setup_image(frame, frame->image);
	frame->draw(frame);
	mlx_put_image_to_window(frame->mlx, frame->window, frame->image->img, 0, 0);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = -1;
		while (++y < SCREEN_HEIGTH)
			frame->screen[x][y] = LAYER_EMPTY;
	}
	mlx_destroy_image(frame->mlx, frame->image->img);
	return (0);
}
