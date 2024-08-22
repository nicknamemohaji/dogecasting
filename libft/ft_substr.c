/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:03:17 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/07 14:52:35 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	ret_len;
	char			*ret;

	ret_len = ft_strlen(s);
	if (ret_len < start)
		return (ft_strdup(""));
	ret_len -= start;
	if (len < ret_len)
		ret_len = len;
	ret = (char *)malloc(sizeof(char) * (ret_len + 1));
	if (ret == NULL)
		return (NULL);
	while (start--)
		s++;
	ft_strlcpy(ret, s, ret_len + 1);
	return (ret);
}
