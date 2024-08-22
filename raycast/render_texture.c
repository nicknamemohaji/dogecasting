/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 05:28:09 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/07 03:05:28 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			render_texture(t_frame *frame,
					t_render_params const *params);
static void		calculate_texture_pos(t_render_params const *params,
					t_vector2i *tex_pos, float *tex_y_counter);
t_texture		*cub3d_texture_create(t_frame *frame, const char *file);
static void		transpose_texture(t_texture *texture, t_image image);

void	render_texture(t_frame *frame, t_render_params const *params)
{
	const t_texture *const	texture = params->texture;
	const int				x = params->x;
	int						y;
	t_vector2i				tex_pos;
	float					tex_yf;

	calculate_texture_pos(params, &tex_pos, &tex_yf);
	y = params->draw_start - 1;
	while (++y <= params->draw_end)
	{
		tex_pos.y = (int)tex_yf;
		tex_yf += params->step;
		ft_mlx_image_put(
			frame,
			(t_vector2i){x, y},
			texture->image[tex_pos.x * texture->height + tex_pos.y]
			);
	}
}

static void	calculate_texture_pos(t_render_params const *params,
				t_vector2i *tex_pos, float *tex_y_counter)
{
	const t_texture	*texture = params->texture;

	tex_pos->x = (int)(params->wall_pos * texture->width);
	if (params->dda_result->side == DIR_W)
		tex_pos->x = texture->width - tex_pos->x - 1;
	if (params->dda_result->side == DIR_S)
		tex_pos->x = texture->width - tex_pos->x - 1;
	if (params->draw_end - params->draw_start == params->line_height)
		*tex_y_counter = 0.0f;
	else
	{
		*tex_y_counter = (params->draw_start
				- (SCREEN_HEIGTH - params->line_height) / 2)
			* params->step;
	}
}

t_texture	*cub3d_texture_create(t_frame *frame, const char *file)
{
	t_texture	*ret;
	void		*texture_mlx_image;
	t_image		image;

	ret = malloc(1 * sizeof(t_texture));
	if (ret == NULL)
		error_exit("cannot allocate memory\n");
	texture_mlx_image = mlx_xpm_file_to_image(frame->mlx, (char *)file,
			&((ret)->width), &((ret)->height));
	if (texture_mlx_image == NULL)
		error_exit("cannot open texture\n");
	ret->image = malloc((ret->height * ret->width) * sizeof(unsigned int));
	if (ret->image == NULL)
		error_exit("cannot allocate memory\n");
	image.img = texture_mlx_image;
	image.addr = mlx_get_data_addr(
			texture_mlx_image, &image.bits_per_pixel, &image.line_length,
			&image.endian);
	if (image.addr == NULL)
		error_exit("cannot get address from mlx.image\n");
	transpose_texture(ret, image);
	mlx_destroy_image(frame->mlx, texture_mlx_image);
	return (ret);
}

static void	transpose_texture(t_texture *texture, t_image image)
{
	const int	height = texture->height;
	const int	width = texture->width;
	int			x;
	int			y;
	char		*dst;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			dst = image.addr + (y * image.line_length
					+ x * (image.bits_per_pixel / 8));
			texture->image[x * height + y] = *(unsigned int *)dst;
		}
	}
}
