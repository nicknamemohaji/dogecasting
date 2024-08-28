/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_meta_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:30:20 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/28 16:20:27 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parser.h"
#include "get_next_line.h"

t_bool	try_fill_color(t_metadata *info, char *line);
void	fill_color(t_metadata *info, int key, char *colors);
t_bool	valid_color_format(char *colors);

t_bool	try_fill_color(t_metadata *info, char *line)
{
	const char	*color_keys[3] = {FLOOR_COLOR, CEILING_COLOR, NULL};
	int			i;

	i = 0;
	while (color_keys[i])
	{
		if (ft_strncmp(color_keys[i], line, COLOR_KEY_LEN) == 0)
			return (fill_color(info, i, line + COLOR_KEY_LEN), TRUE);
		i++;
	}
	return (FALSE);
}

void	fill_color(t_metadata *info, int key, char *colors)
{
	int			color_cnt;
	int			color;
	int			current_color;
	const int	rgb[3] = {16, 8, 0};

	color_cnt = 0;
	color = 0;
	info->colors[key] = 0;
	if (valid_color_format(colors) == FALSE)
		throw_parse_error(ERR_COLOR_FORMAT);
	while (colors && color_cnt < 3)
	{
		while (colors && *colors == ' ')
			colors++;
		current_color = ft_atoi(colors);
		if (!(0 <= current_color && current_color <= 255))
			throw_parse_error(ERR_COLOR_RANGE);
		info->colors[key] += current_color << rgb[color_cnt];
		color_cnt++;
		colors = ft_strchr(colors, ',');
		if (colors)
			colors++;
	}
}

t_bool	valid_color_format(char *colors)
{
	int		color_amount;

	color_amount = 0;
	while (colors && *colors)
	{
		while (*colors == ' ')
			colors++;
		if (*colors == '\0')
			throw_parse_error(ERR_COLOR_FORMAT);
		if (ft_isdigit(*colors) == FALSE)
			throw_parse_error(ERR_COLOR_CHAR);
		color_amount++;
		while (*colors != '\0' && ft_isdigit(*colors) == TRUE)
			colors++;
		if ((color_amount == 3 && *colors != '\0')
			|| (color_amount != 3 && *colors == '\0'))
			throw_parse_error(ERR_COLOR_FORMAT);
		if (color_amount != 3 && *colors != ',')
			throw_parse_error(ERR_COLOR_FORMAT);
		if (colors && *colors)
			colors++;
	}
	if (*colors != '\0' || color_amount != 3)
		throw_parse_error(ERR_COLOR_FORMAT);
	return (TRUE);
}
