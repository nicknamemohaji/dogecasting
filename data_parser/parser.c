/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:11:06 by yechakim          #+#    #+#             */
/*   Updated: 2024/08/28 13:54:35 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_parser.h"

void	initialize_data(t_frame *frame, int argc, char **argv);
int		get_file(char *filename);
t_bool	has_only_one_cub3d_file(int argc, char **argv);
void	set_textures(t_frame *frame, t_metadata *metadata);

void	initialize_data(t_frame *frame, int argc, char **argv)
{
	t_metadata	*metadata;
	int			file_descripter;

	if (!has_only_one_cub3d_file(argc, argv))
		exit(1);
	file_descripter = get_file(argv[1]);
	metadata = ft_calloc(1, sizeof(t_metadata));
	if (!metadata)
		throw_parse_error(NULL);
	metadata->colors[FLOOR] = -1;
	metadata->colors[CEILING] = -1;
	if (!read_metadata(metadata, file_descripter))
		throw_parse_error("Failed to read metadata\n");
	if (!read_map(frame, &frame->map, file_descripter))
		throw_parse_error("Failed to read map\n");
	set_textures(frame, metadata);
	frame->color_ceiling = metadata->colors[CEILING];
	frame->color_floor = metadata->colors[FLOOR];
	free(metadata);
}

int	get_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		throw_parse_error("Failed to open file\n");
	return (fd);
}

t_bool	has_only_one_cub3d_file(int argc, char **argv)
{
	if (argc != 2)
		throw_parse_error("Invalid number of arguments\n");
	if (!is_ext(argv[1], MAP_FILE_EXT))
		throw_parse_error("Invalid file extension\n");
	if (is_exist_file(argv[1]) == FALSE)
		throw_parse_error("File does not exist\n");
	return (TRUE);
}

void	set_textures(t_frame *frame, t_metadata *metadata)
{
	frame->map.textures[DIR_N]
		= cub3d_texture_create(frame, metadata->dir[DIR_N]);
	free(metadata->dir[DIR_N]);
	frame->map.textures[DIR_E]
		= cub3d_texture_create(frame, metadata->dir[DIR_E]);
	free(metadata->dir[DIR_E]);
	frame->map.textures[DIR_W]
		= cub3d_texture_create(frame, metadata->dir[DIR_W]);
	free(metadata->dir[DIR_W]);
	frame->map.textures[DIR_S]
		= cub3d_texture_create(frame, metadata->dir[DIR_S]);
	free(metadata->dir[DIR_S]);
}
