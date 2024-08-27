/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:36:00 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 15:38:27 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"
#include "get_next_line.h"

char	*read_map_lines(int file);
void	fill_mapsize(t_map *map, char **lines);
int		ft_max(int a, int b);

char	*read_map_lines(int file)
{
	char	*line;
	char	*map_str;

	line = get_next_line(file);
	map_str = ft_strdup(line);
	while (TRUE && map_str)
	{
		if (errno != 0)
			throw_parse_error(NULL);
		if (!line)
			break ;
		if (*line == '\n')
		{
			free(line);
			line = ft_strdup(" \n");
			if (!line)
				throw_parse_error(NULL);
		}
		map_str = ft_strjoin_and_free(map_str, line, FREE_S1);
		if (!map_str)
			throw_parse_error(NULL);
		free(line);
		line = get_next_line(file);
	}
	return (map_str);
}

void	fill_mapsize(t_map *map, char **lines)
{
	int	i;

	i = 0;
	map->map_w = 0;
	while (lines[i])
	{
		map->map_w = ft_max(map->map_w, ft_strlen(lines[i]));
		i++;
	}
	map->map_h = i;
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
