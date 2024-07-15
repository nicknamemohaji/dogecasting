/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:20:26 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/11 14:48:35 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void prototype(t_frame *frame);
void check_leak(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	printf("sizeof %lu \n", sizeof(t_dda));
	t_image	mlx_image;
	t_frame	mlx_frame;
	
	ft_mlx_setup(&mlx_frame, &mlx_image);
	initialize_data(&mlx_frame, argc, argv);
	mlx_frame.draw = &cub3d;
	mlx_loop_hook(mlx_frame.mlx, ft_mlx_render, &mlx_frame);
	mlx_loop(mlx_frame.mlx);
}
