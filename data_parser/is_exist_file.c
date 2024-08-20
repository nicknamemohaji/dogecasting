/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exist_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:33:00 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/15 21:11:57 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

int	is_exist_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}
