/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:32:27 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/08 10:56:13 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <errno.h>
#include <stdio.h>

t_com	*ft_read_userinput(char *line)
{
	char	**command;
	t_com	*todo;

	if (ft_beginwith_semicolon(line))
		return (NULL);
	if (!(command = ft_split_command(line)))
		return (NULL);
	if (!(todo = ft_parse_command(command)))
		return (NULL);
	ft_freetab(&command);
	return (todo);
}

char	**ft_split_command(char *s)
{
	char	**command;
	int		len;
	int		check;
	char	*temp;

	command = NULL;
	check = 0;
	while (*s)
	{
		if (*s && *s != ';')
		{
			check = 0;
			len = ft_move_endofcommand(s);
			temp = ft_strsub(s, 0, len);
			ft_addtotab(&command, temp);
			free(temp);
			s = s + len;
		}
		else if (*s && *s++ == ';')
			check++;
		if (ft_check_semicolon(check, &command))
			return (NULL);
	}
	return (command);
}

int		ft_beginwith_semicolon(char *s)
{
	char	*trim;

	trim = ft_strtrim(s);
	if (!*trim)
	{
		free(trim);
		return (1);
	}
	if (*trim && *trim == ';' && *(trim + 1) != ';')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
		free(trim);
		return (1);
	}
	if (*trim && *trim == ';' && *(trim + 1) == ';')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;;'", 2);
		free(trim);
		return (1);
	}
	free(trim);
	return (0);
}

int		ft_check_semicolon(int check, char ***command)
{
	if (check > 1)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;;'", 2);
		if (*command)
			ft_freetab(command);
		return (1);
	}
	return (0);
}

int		ft_move_endofcommand(char *s)
{
	int len;

	len = 0;
	while (*(s + len) && *(s + len) != ';')
	{
		if (*(s + len) && *(s + len) == '"')
		{
			len++;
			while (*(s + len) && *(s + len) != '"')
				len++;
		}
		if (*(s + len))
			len++;
	}
	return (len);
}
