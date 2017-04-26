/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:56:40 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/26 19:25:36 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com 	*parse_command(char **command)
{
	t_com	*todo;
	t_com	*elem;
	char	**wip;
	int		i;

	if ((check_commandblank(command)))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
		ft_freetab(&command);
		return(NULL);
	}

	if ((check_quotes(command)))
	{
		ft_putendl_fd("minishell: missing closing quote \"", 2);
		ft_freetab(&command);
		return(NULL);
	}

	todo = NULL;
	i = 0;
	while (*(command + i))
	{
		wip = split_intoarg(*(command + i));
		elem = sh_lstnew(wip);
		ft_freetab(&wip);
		is_builtin(elem);

		ft_puttab(elem->command);
		ft_putendl("****");

		sh_lstaddlast(&todo, elem);
		i++;
	}
	// ft_puttab(command);
	// ft_freetab(&command);
	return (todo);
}

char	**split_intoarg(char *s)
{
	char **wip;
	int len;
	char *temp;

	wip = NULL;
	while (*s)
	{
		if (*s && !ft_isspace(*s))
		{
			len = move_endofarg(s);
			temp = strsub_withoutquotes(s, len);
			ft_addtotab(&wip, temp);
			free(temp);
			s = s + len;
		}
		else if (*s)
			s++;
	}
	return (wip);
}

int		check_commandblank(char **command)
{
	char	*temp;
	int		i;

	i = 0;
	while (*(command + i))
	{
		temp = *(command + i);
		*(command + i) = ft_strtrim(*(command + i));
		free(temp);
		if (!**(command + i))
			return (1);
		i++;
	}
	return (0);
}

int		check_quotes(char **command)
{
	int		i;
	int		quotes;

	quotes = 0;
	i = 0;
	while (*(command + i))
	{
		quotes = nb_quotes(*(command + i), ft_strlen(*(command + i)));
		if (quotes % 2 != 0)
			return (1);
		i++;
	}
	return (0);
}

void	is_builtin(t_com *elem)
{
	char	**builtin;
	int		i;
	char	*test;

	test = ft_strdup("cd echo env exit setenv unsetenv");
	builtin = ft_strsplit(test, ' ');
	free(test);
	i = 0;
	while (i < 6)
	{
		if (ft_strequ(elem->path, *(builtin + i)))
			elem->builtin = 1 << i;
		++i;
	}
	ft_freetab(&builtin);
}
