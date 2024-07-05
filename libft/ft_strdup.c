/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:00:31 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/06 00:41:18 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		s1_len;
	char	*ret;

	s1_len = ft_strlen(s1);
	ret = (char *)malloc(s1_len + 1);
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, s1, s1_len + 1);
	return (ret);
}
