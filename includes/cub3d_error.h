/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:19:26 by kyungjle          #+#    #+#             */
/*   Updated: 2024/08/27 14:20:54 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ERROR_H
# define CUB3D_ERROR_H

# include <errno.h>
# include <err.h>

# define ERROR_PREFIX "Error: "
# define ERR_EXT "Invalid file extension\n"
# define ERR_OPEN "Failed to open file\n" // delete
# define ERR_DUPLICATE_METADATA "Already Registered Metadata\n"
/* colors */
# define ERR_COLOR "Invalid color: "
# define ERR_COLOR_FORMAT "Invalid color format\n"
# define ERR_COLOR_RANGE "Invalid color range\n"
# define ERR_COLOR_VALUE "Invalid color value\n" 
# define ERR_COLOR_CHAR "Invalid color character\n"
# define ERR_COLOR_FORMAT_WITH_DELIMITER "Invalid color with ','\n"

# define ERR_MAP "Invalid map: "
# define ERR_MAP_CHAR "contains invalid character\n"
# define ERR_MAP_SURROUND "map is not surrounded by walls\n"

#endif //CUB3D
