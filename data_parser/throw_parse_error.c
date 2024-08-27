/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_parse_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:45:48 by yechakim          #+#    #+#             */
/*   Updated: 2024/08/27 17:02:29 by yechakim         ###   ########seoul.kr  */
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
		perror(NULL);
	exit(1);
}
