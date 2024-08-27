/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:09:07 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 18:29:30 by yechakim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

void		ft_mlx_setup(t_frame *frame, t_image *img);
static void	setup_frame(t_frame *frame);
void		ft_mlx_setup_image(t_frame *frame);
static void	setup_hook(t_frame *frame);
void		error_exit(const char *msg);

void	ft_mlx_setup(t_frame *frame, t_image *img)
{
	frame->image = img;
	frame->draw = &cub3d;
	setup_frame(frame);
	setup_hook(frame);
}

static void	setup_frame(t_frame *frame)
{
	frame->mlx = mlx_init();
	if (frame->mlx == NULL)
		error_exit("cannot init mlx\n");
	frame->window = mlx_new_window(frame->mlx, SCREEN_WIDTH,
			SCREEN_HEIGTH, "cub3d");
	if (frame->window == NULL)
		error_exit("cannot init mlx.window\n");
	frame->dda = malloc(SCREEN_WIDTH * sizeof(t_dda));
	if (frame->dda == NULL)
		error_exit("cannot allocate memory\n");
}

void	ft_mlx_setup_image(t_frame *frame)
{
	t_image	*img;

	img = frame->image;
	img->img = mlx_new_image(frame->mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	if (img->img == NULL)
		error_exit("cannot init mlx.image\n");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (img->addr == NULL)
		error_exit("cannot get adress from mlx.image\n");
}

static void	setup_hook(t_frame *frame)
{
	mlx_hook(frame->window, ON_DESTROY, NOEVENTMASK, ft_mlx_destroy, frame);
	mlx_hook(frame->window, ON_KEYDOWN, NOEVENTMASK,
		ft_mlx_event_key, frame);
}

void	error_exit(const char *msg)
{
	ft_putstr_fd(2, msg);
	exit(EXIT_FAILURE);
}
