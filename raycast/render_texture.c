/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 05:28:09 by kyungjle          #+#    #+#             */
/*   Updated: 2024/06/27 12:20:27 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d_render_draw(t_frame *frame, t_render_params params);

void	cub3d_render_draw(t_frame *frame, t_render_params params)
{
	const t_texture	*texture = params.texture;
	t_vector2i		texture_pos;
	double			texture_y_pos_counter;
	int				y;
	int				color;

	texture_pos.x = (int)(params.wall_pos * texture->width);
	if (params.dda_result.side == DIR_W)
		texture_pos.x = texture->width - texture_pos.x - 1;
	if (params.dda_result.side == DIR_N)
		texture_pos.x = texture->width - texture_pos.x - 1;
	texture_y_pos_counter = (params.draw_start
			- (SCREEN_HEIGTH + params.line_height) / 2) * params.step;
	y = params.draw_start - 1;
	while (++y < params.draw_end)
	{
		texture_pos.y = (int)texture_y_pos_counter & (texture->height - 1);
		texture_y_pos_counter += params.step;
		color = ft_mlx_image_color(params.texture->image,
				texture_pos.x, texture_pos.y);
		ft_mlx_image_put(frame,
			(t_vector2i){params.x, y}, color, LAYER_RENDER);
	}
}
