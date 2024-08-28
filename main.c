/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:20:26 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/28 17:17:56 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_image	mlx_image;
	t_frame	mlx_frame;

	ft_mlx_setup(&mlx_frame, &mlx_image);
	initialize_data(&mlx_frame, argc, argv);
	mlx_frame.event = TRUE;
	mlx_loop(mlx_frame.mlx);
}
