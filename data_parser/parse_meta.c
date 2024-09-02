/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:16:21 by kyungjle          #+#    #+#             */
/*   Updated: 2024/09/02 14:21:51 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"
#include "get_next_line.h"

t_bool	read_metadata(t_metadata *metadata, int fd);
t_bool	parse_metadata(t_metadata *info, char *line);
t_bool	is_fullfilled(t_metadata *metadata);

t_bool	read_metadata(t_metadata *metadata, int fd)
{
	char	*line;
	char	*trimedline;

	while (!is_fullfilled(metadata))
	{
		errno = 0;
		line = get_next_line(fd);
		if (errno != 0)
			throw_parse_error(NULL);
		if (!line)
			return (FALSE);
		trimedline = ft_strtrim(line, " \n");
		free(line);
		if (!trimedline)
			throw_parse_error(NULL);
		if (*trimedline != '\0')
		{
			if (ft_strchr("NSWEFC", trimedline[0]) == NULL
				|| parse_metadata(metadata, trimedline) == FALSE)
				return (FALSE);
		}
		free(trimedline);
	}
	return (TRUE);
}

t_bool	parse_metadata(t_metadata *info, char *line)
{
	return (try_fill_direction(info, line) || try_fill_color(info, line));
}

t_bool	is_fullfilled(t_metadata *metadata)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (metadata->dir[i] == NULL)
			return (FALSE);
		i++;
	}
	if (metadata->colors[CEILING] == -1 || metadata->colors[FLOOR] == -1)
		return (FALSE);
	return (TRUE);
}
