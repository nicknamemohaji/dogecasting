/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:52:36 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/07 11:55:11 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	ret;
	int	temp;
	int	sign;

	ret = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-' )
		{
			sign = -1;
		}
		str++;
	}
	while (*str)
	{
		temp = *str;
		if (ft_isdigit(*str) == 0)
			return (ret);
		ret = (ret * 10) + ((temp - '0') * sign);
		str++;
	}
	return (ret);
}
