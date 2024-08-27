/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:24 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 14:19:03 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// custom types
# include "cub3d_types.h"

// mlx interface
# include "mlx.h"

// parser interface
void		initialize_data(t_frame *frame, int argc, char **argv);

// renderer/texture interface
t_texture	*cub3d_texture_create(t_frame *frame, const char *file);

// renderer interface
void		ft_mlx_setup(t_frame *frame, t_image *img);
int			ft_mlx_render(t_frame *frame);

#endif
