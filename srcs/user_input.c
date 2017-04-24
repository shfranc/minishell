/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:32:27 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/24 18:10:23 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <errno.h>
#include <stdio.h>

t_com 	*read_userinput(char **line)
{
	t_com	*elem;
	char	**input;
	char	*temp;
	int		i;

	temp = *line;
	*line = ft_strtrim(*line);
	free(temp);
	if (!**line)
		return (NULL);

	ft_putstr(*line);
	ft_putendl("*");

	input = ft_strsplit(*line, ' ');

	i = 0;
	while (input[i])
	{
		temp = input[i];
		input[i] = ft_strtrim(input[i]);
		free(temp);
		i++;
	}

	ft_puttab(input);
	ft_putendl("**");

	elem = sh_lstnew(input);

	// ft_freetab(&input);
	
	is_builtin(elem);
	// printbit(elem->builtin);
	
	if (!elem->builtin && access(*input, F_OK) == -1)
	{
		ft_putstr("==> ");
		perror(strerror(errno));
	}

	return (elem);
}

void	is_builtin(t_com *elem)
{
	static char	*builtin;
	// [6] = {"cd", "echo", "env", "exit", "setenv", "unsetenv"};
	int			i;

	(builtin + 0) = ft_strdup("cd");
	builtin[1] = ft_strdup("echo");
	builtin[2] = ft_strdup("env");
	builtin[3] = ft_strdup("exit");
	builtin[4] = ft_strdup("setenv");
	builtin[5] = ft_strdup("unsetenv");
	i = 0;
	while (*(builtin = i))
	{
		if (ft_strequ(elem->path, builtin[i]))
			elem->builtin = 1 << i;
		++i;
	}
}