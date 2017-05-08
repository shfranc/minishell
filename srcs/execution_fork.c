/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:23:39 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/08 11:08:19 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_command(t_com *todo, char ***env)
{
	t_com	*temp;

	temp = todo;
	while (temp)
	{
		if (!ft_launch_builtin(temp, env))
		{
			if (ft_launch_command(temp, *env))
			{
				if (signal(SIGINT, ft_handler_child) == SIG_ERR)
					ft_exit("minishell: unable to catch the signal", 1);
				ft_fork(temp, *env);
			}
		}
		temp = temp->next;
	}
}

int		ft_launch_builtin(t_com *todo, char ***env)
{
	int status;

	status = 6;
	todo->builtin == CD ? ft_builtin_cd(todo, env) : status--;
	todo->builtin == ECHO ? ft_builtin_echo(todo) : status--;
	todo->builtin == ENV ? ft_builtin_env(todo, env) : status--;
	todo->builtin == EXIT ? ft_builtin_exit(todo) : status--;
	todo->builtin == SETENV ? ft_builtin_setenv(todo, env) : status--;
	todo->builtin == UNSETENV ? ft_builtin_unsetenv(todo, env) : status--;
	return (status);
}

void	ft_fork(t_com *elem, char **env)
{
	pid_t	new;
	int		status;

	status = 0;
	if ((new = fork()) == -1)
		ft_exit("minishell: Fork failed", 1);
	else if (new == 0)
	{
		if ((status = execve(elem->path, elem->command, env)) == -1)
			ft_exit("minishell: execve: an error has occurred", 2);
	}
	else
		wait(&status);
}
