// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parser.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/05 15:59:59 by yechakim          #+#    #+#             */
// /*   Updated: 2024/07/05 16:58:54 by yechakim         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "cub3d_parser.h"

void initialize_data(t_frame *frame, int argc, char **argv)
{
	if (!has_only_one_cub3d_file(argc, argv))
		exit(1);
}
