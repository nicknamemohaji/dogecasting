/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:35:57 by yechakim          #+#    #+#             */
/*   Updated: 2024/07/10 14:37:26 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

t_bool	has_only_one_cub3d_file(int argc, char **argv)
{
	if (argc != 2)
		throw_parse_error("Invalid number of arguments\n");
	if (!is_ext(argv[1], EXT))
		throw_parse_error("Invalid file extension\n");
	if (is_exist_file(argv[1]) == FALSE)
		throw_parse_error("File does not exist\n");
	return (TRUE);
}