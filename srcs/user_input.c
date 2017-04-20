/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:32:27 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/20 17:20:55 by sfranc           ###   ########.fr       */
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
	// remplacer tous les '\t' ou '\n' par des ' ' pour n'avoir qu'un split a faire

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

	is_builtin(elem);
	printbit(elem->builtin);
	
	if (!elem->builtin && access(*input, F_OK) == -1)
	{
		ft_putstr("==> ");
		perror(strerror(errno));
	}

	return (elem);
}

void	is_builtin(t_com *elem)
{
	static char	*builtin[6] = {"cd", "echo", "env", "exit", "setenv", "unsetenv"};
	int			i;

	i = 0;
	while (builtin[i])
	{
		if (ft_strequ(elem->path, builtin[i]))
			elem->builtin = 1 << i;
		++i;
	}
}