/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_parse_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:45:48 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/05 17:47:48 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

void throw_parse_error(char *msg)
{
	ft_putstr_fd(ERROR_MSG, 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}