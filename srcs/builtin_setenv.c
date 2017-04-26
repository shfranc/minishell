/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 09:32:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/26 18:26:04 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_setenv(t_com *input, char ***env)
{
	char	*temp;
	
	(void)temp;
	(void)env;

	if (!input->command[1])
	{
		ft_putendl_fd("minishell: setenv: too few arguments", 2);
		return ;
	}
	if (!parsing_setenv(input, &temp))
		return ;
	if (!modify_variable(temp, env))
		ft_addtotab(env, temp);
	ft_strdel(&temp);
}

int		parsing_setenv(t_com *input, char **temp)
{
	if (input->command[1][0] == '=')
	{
		ft_putendl_fd("minishell: setenv: '=' is not a valid variable name", 2);
		return (0);
	}
	if (ft_strchr(input->command[1], '='))
	{
		if (!input->command[2])
			*temp = ft_strdup(input->command[1]);
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
		*temp = ft_strjoin3(input->command[1], "=", input->command[2]);
	return (1);
}

int		modify_variable(char *name, char ***env)
{
	char	*to_free;
	int		i;

	i = 0;
	while (*(*env + i))
	{
		if ((ft_strncmp(*(*env + i), name,\
			ft_strchr(*(*env + i), '=') - *(*env + i))) == 0)
		{
			to_free = *(*env + i);
			*(*env + i) = ft_strdup(name);
			free(to_free);
			return (1);
		}
		i++;
	}
	return (0);
}

// void	adding_variable(char *name, char ***env)
// {
// 	int		len;
// 	int		i;
// 	char	**new;
// 	char	**old;

// 	len = ft_tablen(*env) + 1;
// 	if (!(new = (char**)malloc(sizeof(char*) * (len + 1))))
// 		ft_exit("Unable to malloc env", 1);
// 	*(new + len) = 0;
// 	i = 0;
// 	while (*(*env + i))
// 	{
// 		*(new + i) = *(*env + i);
// 		++i;
// 	}
// 	*(new + i) = ft_strdup(name);
// 	old = *env;
// 	*env = new;
// 	free(old);
// }
