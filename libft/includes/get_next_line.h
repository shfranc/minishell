/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:14:53 by sarah             #+#    #+#             */
/*   Updated: 2017/04/18 10:16:13 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFF_SIZE 42

typedef struct	s_file
{
	int				fd;
	char			*buff;
	struct s_file	*next;
}				t_file;

t_file			*create_file(int fd);
t_file			*collect_or_create(t_file **start, int fd);
void			fill_line(char *buff, char **line);
int				empty_buff(char *buff, char **line);
int				get_next_line(const int fd, char **line);

#endif
