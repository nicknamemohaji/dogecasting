/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechakim <yechakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:36:31 by yechakim          #+#    #+#             */
/*   Updated: 2024/04/15 19:52:32 by yechakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static void	*gnl_free_node(t_fd_node **list, int fd)
{
	t_fd_node	*head;

	head = *list;
	if (head == NULL)
		return (NULL);
	if (head->fd == fd)
	{
		*list = NULL;
		if (head->buffer)
		{
			free(head->buffer);
			head->buffer = NULL;
		}
		free(head);
		return (NULL);
	}
	return (NULL);
}

static t_fd_node	*gnl_get_node(t_fd_node **list, int fd)
{
	t_fd_node	*node;

	if (*list)
		return (*list);
	node = (t_fd_node *)malloc(sizeof(t_fd_node));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->next = NULL;
	node->readsize = BUFFER_SIZE;
	node->buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!node->buffer)
		return (gnl_free_node(&node, fd));
	*(node->buffer) = 0;
	*list = node;
	return (node);
}

static char	*gnl_has_line(t_fd_node **list)
{
	char	*ret;
	char	*rest;

	ret = NULL;
	if (!(*list) || !(*list)->buffer)
		return (NULL);
	rest = ft_strchr((*list)->buffer, '\n');
	if (rest != NULL)
	{
		rest++;
		ret = ft_substr((*list)->buffer, 0, (rest - ((*list)->buffer)));
		if (!ret)
			return (gnl_free_node(list, (*list)->fd));
		ft_strlcpy((*list)->buffer, rest, ft_strlen(rest) + 1);
		return (ret);
	}
	rest = ft_strchr((*list)->buffer, '\0');
	if (rest != NULL && (*list)->readsize != BUFFER_SIZE)
	{
		ret = ft_substr((*list)->buffer, 0, (rest - ((*list)->buffer)));
		*((*list)->buffer) = 0;
	}
	return (ret);
}

static void	*gnl_read_line(t_fd_node **list, int fd)
{
	char		*buffer;
	t_fd_node	*target;

	target = gnl_get_node(list, fd);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (gnl_free_node(list, (target)->fd));
	*buffer = '\0';
	while (1)
	{
		target->readsize = read(target->fd, (buffer), BUFFER_SIZE);
		if (target->readsize < 0)
		{
			free(target->buffer);
			target->buffer = NULL;
			break ;
		}
		buffer[(target->readsize)] = 0;
		target->buffer = ft_strjoin_and_free((target->buffer), buffer, FREE_S1);
		if ((target->buffer == NULL) || ((target->readsize < BUFFER_SIZE
					|| ft_strchr(buffer, '\n'))))
			break ;
	}
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_fd_node	*list = NULL;
	t_fd_node			*target;
	char				*ret;

	ret = NULL;
	target = gnl_get_node(&list, fd);
	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE < 1 || !target || !target->buffer)
		return (gnl_free_node(&list, fd));
	ret = gnl_has_line(&list);
	if (ret && *ret != '\0')
		return (ret);
	else if (ret)
		free(ret);
	gnl_read_line(&list, fd);
	if (gnl_get_node(&list, fd)->buffer == NULL)
		return (gnl_free_node(&list, fd));
	ret = gnl_has_line(&list);
	if (list && list->buffer && !ft_strlen(list->buffer) && ret && *ret == 0)
	{
		free(ret);
		ret = NULL;
	}
	if (list && ((list->buffer && !ft_strlen(list->buffer)) || !(list->buffer)))
		gnl_free_node(&list, fd);
	return (ret);
}
