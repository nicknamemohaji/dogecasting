/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_and_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:57 by yechakim          #+#    #+#             */
/*   Updated: 2024/04/17 15:46:57 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Join two strings and free the target string.
 * 
 * @param s1 The first string that must be valid.
 * @param s2 The second string that must be valid.
 * @param free_target The target string to free.
 * @return char* The new string.
 */
char	*ft_strjoin_and_free(char *s1, char *s2, t_free_type free_target)
{
	int		s1_len;
	int		s2_len;
	char	*ret;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (ret == NULL)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy((ret + s1_len), s2, s2_len + 1);
	if (free_target & FREE_S1)
		free(s1);
	if (free_target & FREE_S2)
	{
		free(s2);
		*s2 = 0;
	}
	return (ret);
}
