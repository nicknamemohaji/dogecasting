/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:03:01 by yechakim          #+#    #+#             */
/*   Updated: 2023/10/05 19:45:26 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1);
	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	while (s1[start] != 0 && ft_strchr(set, s1[start]))
		start++;
	if (start == end)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, start, (end - start + 1)));
}
