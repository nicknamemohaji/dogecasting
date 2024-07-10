/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:31:36 by kyungjle          #+#    #+#             */
/*   Updated: 2024/07/07 03:08:11 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector2d	ft_vector2d_add(t_vector2d n1, t_vector2d n2);
t_vector2d	ft_vector2d_mul(t_vector2d vec, double scalar);
t_vector2d	ft_vector2d_rotate(t_vector2d vec, double rad);
t_vector2i	ft_vector2i_add(t_vector2i n1, t_vector2i n2);

t_vector2d	ft_vector2d_add(t_vector2d n1, t_vector2d n2)
{
	t_vector2d	ret;

	ret.x = n1.x + n2.x;
	ret.y = n1.y + n2.y;
	return (ret);
}

t_vector2d	ft_vector2d_mul(t_vector2d vec, double scalar)
{
	vec.x *= scalar;
	vec.y *= scalar;
	return (vec);
}

t_vector2d	ft_vector2d_rotate(t_vector2d vec, double rad)
{
	const double	rad_sin = sin(rad);
	const double	rad_cos = cos(rad);
	t_vector2d		old_vec;

	old_vec = vec;
	vec.x = old_vec.x * rad_cos - old_vec.y * rad_sin;
	vec.y = old_vec.x * rad_sin + old_vec.y * rad_cos;
	return (vec);
}

t_vector2i	ft_vector2i_add(t_vector2i n1, t_vector2i n2)
{
	t_vector2i	ret;

	ret.x = n1.x + n2.x;
	ret.y = n1.y + n2.y;
	return (ret);
}
