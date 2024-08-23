/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_parse_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:45:48 by yechakim          #+#    #+#             */
/*   Updated: 2024/08/23 10:50:16 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"
#include "cub3d_error.h"
#include <stdio.h>

void	throw_parse_error(char *msg)
{
	ft_putstr_fd(ERROR_PREFIX, 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	else
	{
		printf("here\n");
		perror(NULL);
	}
	exit(1);
}
