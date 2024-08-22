/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 03:10:47 by yechakim          #+#    #+#             */
/*   Updated: 2024/04/17 15:51:07 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief free all strings in strs and free strs
 * 
 * @param strs it is a null-terminated array of strings
 * @return void* return NULL
*/
void	*ft_free_strs(char **strs)
{
	char	**str_addr;

	str_addr = strs;
	while (*strs)
	{
		free(*strs);
		strs++;
	}
	free(str_addr);
	return (NULL);
}
