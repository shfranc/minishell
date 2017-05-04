/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:23:39 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/04 15:11:09 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_com *todo, char ***env)
{
	t_com	*start;
	int		status;
	pid_t	new;

	status = 0;
	start = todo;
	while (todo)
	{
		if (!launch_builtin(todo, env))
		{
			if (launch_command(todo, *env))
			{
				if ((new = fork()) == -1)
					ft_exit("Fork failed", 1);
				else if (new == 0)
					status = execve(todo->path, todo->command, *env);
				else
					wait(0);
			}
		}
		if (status == -1)
			ft_exit("Kill ghost processus", 1);
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
