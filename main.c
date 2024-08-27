/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:20:26 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 15:47:11 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO DELETE THIS
#include <stdlib.h>
void	check_leak(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_image	mlx_image;
	t_frame	mlx_frame;

	atexit(check_leak);
	ft_mlx_setup(&mlx_frame, &mlx_image);
	initialize_data(&mlx_frame, argc, argv);
	ft_mlx_render(&mlx_frame);
	mlx_loop(mlx_frame.mlx);
}
