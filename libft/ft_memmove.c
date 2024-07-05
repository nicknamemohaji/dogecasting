/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:59:45 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/05 12:05:23 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dstaddr;
	char	*srcaddr;

	if (dst == src || len == 0)
		return (dst);
	dstaddr = (char *)dst;
	srcaddr = (char *)src;
	if (dst > src)
	{
		while (len--)
			*(char *)(dst + len) = *(char *)(src + len);
	}
	else
	{
		while (len--)
			*(char *)(dst++) = *(char *)(src++);
	}
	return (dstaddr);
}
