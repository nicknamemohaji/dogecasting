/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:59:13 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/06 20:30:28 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dstaddr;

	if (dst == src || n == 0)
		return (dst);
	dstaddr = dst;
	while (n)
	{
		*(char *)dst = *(char *)src;
		src++;
		dst++;
		n--;
	}
	return (dstaddr);
}
