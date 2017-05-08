/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 09:32:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/08 11:08:36 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_setenv(t_com *input, char ***env)
{
	char	*new_var;

	if (!input->command[1])
	{
		ft_putendl_fd("minishell: setenv: too few arguments", 2);
		return ;
	}
	if (!ft_parsing_setenv(input, &new_var))
		return ;
	if (!ft_modify_variable(env, new_var))
		ft_addtotab(env, new_var);
	ft_strdel(&new_var);
}

int		ft_parsing_setenv(t_com *input, char **new_var)
{
	if (input->command[1][0] == '=')
	{
		ft_putendl_fd("minishell: setenv: '=' is not a valid variable name", 2);
		return (0);
	}
	if (ft_strchr(input->command[1], '='))
	{
		if (!input->command[2])
			*new_var = ft_strdup(input->command[1]);
		else
		{
			ft_putendl_fd("minishell: setenv: wrong number of arguments", 2);
			return (0);
		}
	}
	else if (!input->command[2] || input->command[3])
	{
		ft_putendl_fd("minishell: setenv: wrong number of arguments", 2);
		return (0);
	}
	else
		*new_var = ft_strjoin3(input->command[1], "=", input->command[2]);
	return (1);
}

int		ft_modify_variable(char ***env, char *new_var)
{
	char	*to_free;
	int		i;

	i = 0;
	while (*(*env + i))
	{
		if ((ft_strncmp(*(*env + i), new_var,\
			ft_strchr(*(*env + i), '=') - *(*env + i))) == 0)
		{
			to_free = *(*env + i);
			*(*env + i) = ft_strdup(new_var);
			free(to_free);
			return (1);
		}
		i++;
	}
	return (0);
}
