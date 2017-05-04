/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 12:22:14 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/28 16:54:05 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_file	*create_file(int fd)
{
	t_file	*new;

	if (!(new = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	new->fd = fd;
	if (!(new->buff = ft_strnew(BUFF_SIZE)))
		return (NULL);
	new->next = NULL;
	return (new);
}

t_file	*collect_or_create(t_file **start, int fd)
{
	t_file	*temp;
	t_file	*file;

	if (*start == NULL)
	{
		*start = create_file(fd);
		return (*start);
	}
	file = *start;
	while (file)
	{
		if (file->fd == fd)
			return (file);
		file = file->next;
	}
	if (file == NULL)
	{
		temp = *start;
		*start = create_file(fd);
		(*start)->next = temp;
		return (*start);
	}
	return (NULL);
}

void	fill_line(char *buff, char **line)
{
	char	*temp;

	if (*line)
	{
		temp = *line;
		*line = ft_strjoin(temp, buff);
		ft_strdel(&temp);
	}
	else
		*line = ft_strdup(buff);
	ft_bzero(buff, BUFF_SIZE);
}

int		empty_buff(char *buff, char **line)
{
	char	*stop;
	char	*to_keep;

	if (!buff || *buff == 0)
		return (0);
	if ((stop = ft_strchr(buff, '\n')))
	{
		*stop = '\0';
		to_keep = ft_strdup(stop + 1);
		fill_line(buff, line);
		buff = ft_strcpy(buff, to_keep);
		ft_strdel(&to_keep);
		return (1);
	}
	else
		fill_line(buff, line);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_file	*file;
	t_file			*temp;
	int				ret;

	if (!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	*line = NULL;
	if (!(temp = collect_or_create(&file, fd)))
		return (-1);
	if (empty_buff(temp->buff, line) == 1)
		return (1);
	while ((ret = read(temp->fd, temp->buff, BUFF_SIZE)) > 0)
	{
		if (empty_buff(temp->buff, line) == 1)
			return (1);
	}
	if (ret < 0)
		return (-1);
	if (*line != NULL)
	{
		ft_strdel(&temp->buff);
		return (1);
	}
	return (0);
}
