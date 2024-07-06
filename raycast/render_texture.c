/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 05:28:09 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/07 01:28:50 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		render_texture(t_frame *frame,
				t_render_params const *params);
static void	calculate_texture_pos(t_render_params const *params,
				t_vector2i *tex_pos, float *tex_y_counter);

void	render_texture(t_frame *frame, t_render_params const *params)
{
	const int		x = params->x;
	int				y;
	t_vector2i		tex_pos;
	float			tex_yf;

	calculate_texture_pos(params, &tex_pos, &tex_yf);
	y = params->draw_start - 1;
	while (++y <= params->draw_end)
	{
		tex_pos.y = (int)tex_yf;
		tex_yf += params->step;
		ft_mlx_image_put(
			frame,
			(t_vector2i){x, y},
			ft_mlx_image_color(params->texture->image,
				tex_pos.x, tex_pos.y)
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
