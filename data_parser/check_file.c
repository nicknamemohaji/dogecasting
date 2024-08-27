/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:45:23 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 15:46:01 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"

int	is_ext(char *str, char *ext);
int	is_exist_file(char *filename);

int	is_ext(char *file, char *ext)
{
	char	*file_ext;

	if (!file || !ext)
		return (0);
	file_ext = ft_strrchr(file, '.');
	if (!file_ext)
		return (0);
	return (ft_strncmp(file_ext, ext, ft_strlen(ext) + 1) == 0);
}

int	is_exist_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}
