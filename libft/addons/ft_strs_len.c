/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:14:17 by yechakim          #+#    #+#             */
/*   Updated: 2024/04/17 15:53:12 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief count the number of strings in strs
 * 
 * @param strs it is a null-terminated array of strings
 * @return size_t the number of strings in strs
*/
size_t	ft_strs_len(const char **strs)
{
	size_t	ret;

	ret = 0;
	while (strs[ret])
		ret++;
	return (ret);
}
