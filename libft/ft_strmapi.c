/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 03:46:22 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/07 11:54:59 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		idx;
	char	*ret;

	idx = 0;
	if (s == NULL)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s)+1));
	if (ret == NULL)
		return (NULL);
	while (s[idx])
	{
		ret[idx] = f(idx, s[idx]);
		idx++;
	}
	ret[idx] = 0;
	return (ret);
}
