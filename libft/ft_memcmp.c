/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:55:33 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/06 00:40:59 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			break ;
		n--;
		s1++;
		s2++;
	}
	if (n == 0)
	{
		s1--;
		s2--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
