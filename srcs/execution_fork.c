/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:23:39 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/05 19:58:46 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_com *todo, char ***env)
{
	t_com	*start;
	pid_t	new;
	int		status;

	start = todo;
	status = 0;
	while (todo)
	{
		if (!launch_builtin(todo, env))
		{
			if (launch_command(todo, *env))
			{
				if ((new = fork()) == -1)
					ft_exit("minishell: Fork failed", 1);
				else if (new == 0)
				{
					if ((status = execve(todo->path, todo->command, *env)) == -1)
						ft_exit("minishell: execve: an error has occurred", 2);
				}
				else
				{
					ft_putstr("status:");
					ft_putnbr_endl(status);
					wait(&status);
				}
			}
		}
		todo = todo->next;
	}
	sh_lstdel(&start);
}

int		launch_builtin(t_com *todo, char ***env)
{
	int status;

	status = 6;
	todo->builtin == CD ? builtin_cd(todo, env) : status--;
	todo->builtin == ECHO ? builtin_echo(todo) : status--;
	todo->builtin == ENV ? builtin_env(todo, env) : status--;
	todo->builtin == EXIT ? builtin_exit(todo) : status--;
	todo->builtin == SETENV ? builtin_setenv(todo, env) : status--;
	todo->builtin == UNSETENV ? builtin_unsetenv(todo, env) : status--;
	return (status);
}
