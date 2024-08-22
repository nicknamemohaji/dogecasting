/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 23:30:16 by yechakim          #+#    #+#             */
/*   Updated: 2024/04/15 17:50:15 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# if BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fd_node
{
	int					fd;
	size_t				readsize;
	char				*buffer;
	struct s_fd_node	*next;
}						t_fd_node;

typedef struct s_handler
{
	char				*public_buffer;
	t_fd_node			*list;
}						t_handler;

char					*get_next_line(int fd);
#endif