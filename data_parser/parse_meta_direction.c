/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta_direction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:23:06 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 15:30:13 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

t_bool	try_fill_direction(t_metadata *info, char *line);
t_bool	fill_direction(t_metadata *info, t_dir dir, char *line);

t_bool	try_fill_direction(t_metadata *info, char *line)
{
	const char	*dir_keys[5] = {NORTH, SOUTH, WEST, EAST, NULL};
	int			i;

	i = 0;
	while (dir_keys[i])
	{
		if (ft_strncmp(dir_keys[i], line, DIR_KEY_LEN) == 0)
		{
			if (info->dir[i] != NULL)
				throw_parse_error(ERR_DUPLICATE_METADATA);
			fill_direction(info, i, line + DIR_KEY_LEN);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	fill_direction(t_metadata *info, t_dir dir, char *line)
{
	int	fd;

	while (line && *line == ' ')
		line++;
	if (is_ext(line, VALID_TEXTURE_EXT) == FALSE)
		throw_parse_error(ERR_EXT);
	info->dir[dir] = ft_strdup(line);
	fd = open(line, O_RDONLY);
	if (fd < 0)
	{
		printf("err in open\n");
		throw_parse_error(NULL);
	}
	close(fd);
	return (TRUE);
}
