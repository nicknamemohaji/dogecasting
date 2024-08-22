/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 02:27:52 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/04 07:34:13 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d_interface(t_frame *frame, const t_map *map,
			const t_vector2d player_pos);

void	cub3d_interface(t_frame *frame, const t_map *map,
			const t_vector2d player_pos)
{
	interface_minimap(frame, map, player_pos);
}
