/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 05:28:09 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/04 04:29:54 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d_render_draw(t_frame *frame, t_render_params *params);

void	cub3d_render_draw(t_frame *frame, t_render_params *params)
{
	const t_texture	*texture = params->texture;
	t_vector2i		texture_pos;
	float			texture_pos_yf;
	int				y;
	int				color;

	texture_pos.x = (int)(params->wall_pos * texture->width);
	if (params->dda_result.side == DIR_W)
		texture_pos.x = texture->width - texture_pos.x - 1;
	if (params->dda_result.side == DIR_N)
		texture_pos.x = texture->width - texture_pos.x - 1;
	texture_pos_yf = (params->draw_start
			- (SCREEN_HEIGTH + params->line_height) / 2) * params->step;
	if (texture_pos_yf < 0)
		texture_pos_yf = 0;
	y = params->draw_start - 1;
	while (++y <= params->draw_end)
	{
		texture_pos.y = (int)texture_pos_yf;
		texture_pos_yf += params->step;
		color = ft_mlx_image_color(params->texture->image,
				texture_pos.x, texture_pos.y);
		ft_mlx_image_put(frame,
			(t_vector2i){params->x, y}, color, LAYER_RENDER);
	}
}
