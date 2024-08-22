/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ext.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:01:28 by yechakim          #+#    #+#             */
/*   Updated: 2024/08/20 10:38:03 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"
#include <stdio.h>

int	is_ext(char *file, char *ext)
{
	char	*file_ext;

	if (!file || !ext)
		return (0);
	file_ext = ft_strrchr(file, '.');
	if (!file_ext)
		return (0);
	return (ft_strncmp(file_ext, ext, ft_strlen(ext) + 1) == 0);
}
