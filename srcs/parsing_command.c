/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:56:40 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/08 11:12:03 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	*ft_parse_command(char **command)
{
	t_com	*todo;

	if ((ft_check_commandblank(command)))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
		ft_freetab(&command);
		return (NULL);
	}
	if ((ft_check_quotes(command)))
	{
		ft_putendl_fd("minishell: missing closing quote `\"'", 2);
		ft_freetab(&command);
		return (NULL);
	}
	todo = NULL;
	ft_create_cmd_list(&todo, command);
	return (todo);
}

void	ft_create_cmd_list(t_com **todo, char **command)
{
	t_com	*elem;
	char	**wip;
	int		i;

	i = 0;
	while (*(command + i))
	{
		wip = ft_split_intoarg(*(command + i));
		elem = ft_sh_lstnew(wip);
		ft_freetab(&wip);
		ft_is_builtin(elem);
		ft_sh_lstaddlast(&*todo, elem);
		i++;
	}
}

char	**ft_split_intoarg(char *s)
{
	char	**wip;
	int		len;
	char	*temp;

	wip = NULL;
	while (*s)
	{
		if (*s && !ft_isspace(*s))
		{
			len = ft_move_endofarg(s);
			temp = ft_strsub_withoutquotes(s, len);
			ft_addtotab(&wip, temp);
			free(temp);
			s = s + len;
		}
		else if (*s)
			s++;
	}
	return (wip);
}

int		ft_check_commandblank(char **command)
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

int		ft_check_quotes(char **command)
{
	int		i;
	int		quotes;

	quotes = 0;
	i = 0;
	while (*(command + i))
	{
		quotes = ft_nb_quotes(*(command + i), ft_strlen(*(command + i)));
		if (quotes % 2 != 0)
			return (1);
		i++;
	}
	return (0);
}
