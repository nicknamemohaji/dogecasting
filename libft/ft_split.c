/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:15:42 by yechakim          #+#    #+#             */
/*   Updated: 2024/04/17 15:57:47 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	word_cnt;
	int	is_word;

	word_cnt = 0;
	is_word = 0;
	while (*str)
	{
		while (*str && *str == c)
		{
			is_word = 0;
			str++;
		}
		while (*str && *str != c)
		{
			is_word = 1;
			str++;
		}
		while (*str && *str == c)
			str++;
		if (is_word == 0)
			break ;
		word_cnt++;
		is_word = 0;
	}
	return (word_cnt);
}

static int	ft_word_len(char const *str, char end)
{
	int	word_len;

	word_len = 0;
	while (str[word_len] && str[word_len] != end)
			word_len++;
	return (word_len);
}

char	**ft_split(char const *s, char c)
{
	char	**origin;
	char	**temp;
	int		word_len;

	temp = (char **)malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (temp == NULL)
		return (NULL);
	origin = temp;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		word_len = ft_word_len(s, c);
		if (word_len == 0)
			continue ;
		*temp = ft_substr(s, 0, word_len);
		if (*temp == NULL)
			return (ft_free_strs(origin));
		s += word_len;
		temp++;
	}
	*temp = NULL;
	return (origin);
}
