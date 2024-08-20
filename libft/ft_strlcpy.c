/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:01:15 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/06 09:04:53 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{	
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (dstsize > 1 && *src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	*dst = '\0';
	return (src_len);
}
