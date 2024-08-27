/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:01:47 by yechakim          #+#    #+#             */
/*   Updated: 2024/08/27 14:21:40 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSER_H
# define CUB3D_PARSER_H

# include "cub3d_constants.h"
# include "cub3d_types.h"
# include "libft.h"
# include <sys/fcntl.h>

/** CONSTNATS FOR PARSER */
typedef char	*t_metadata_key;
typedef struct s_metadata
{
	char	*dir[TEXTURE_AMOUNT];
	int		colors[2];
}	t_metadata;

typedef enum e_color
{
	FLOOR,
	CEILING
}	t_color;

/* API */
void	initialize_data(t_frame *frame, int argc, char **argv);

/* UTILS */

void	throw_parse_error(char *msg);
int		is_ext(char *str, char *ext);
int		is_exist_file(char *filename);
t_bool	has_only_one_cub3d_file(int argc, char **argv);

#endif
