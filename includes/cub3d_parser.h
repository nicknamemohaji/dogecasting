/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:01:47 by yechakim          #+#    #+#             */
/*   Updated: 2024/08/27 15:48:36 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSER_H
# define CUB3D_PARSER_H

# include "cub3d_constants.h"
# include "cub3d_types.h"
# include "libft.h"

# include <sys/fcntl.h>
# include <stdio.h>

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

# define SPACE 2

/* API */
void	initialize_data(t_frame *frame, int argc, char **argv);

/* UTILS */

void	throw_parse_error(char *msg);
int		is_ext(char *str, char *ext);
int		is_exist_file(char *filename);

/* METADATA */
t_bool	read_metadata(t_metadata *metadata, int fd);
t_bool	try_fill_direction(t_metadata *info, char *line);
t_bool	try_fill_color(t_metadata *info, char *line);

/* MAP */
t_bool	read_map(t_frame *frame, t_map *map, int file);
char	*read_map_lines(int file);
void	fill_mapsize(t_map *map, char **lines);
void	fill_map(t_frame *frame, t_map *map, char **lines);
void	validate_map(t_frame *frame, t_map *map);

#endif
