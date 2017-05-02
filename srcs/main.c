/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:55:07 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/02 13:42:50 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(char **env)
{
	char *user;
	char *cwd;

	ft_putstr(BCYAN);
	if ((user = get_env_variable(env, "USER=")))
	{
		ft_putstr(user);
		ft_putstr(": ");
	}
	else
		ft_putstr("minishell: ");
	free(user);
	ft_putstr(RESET);
	
	ft_putstr(BBLUE);
	if ((cwd = getcwd(NULL, 0)))
		ft_putstr(cwd);
	free(cwd);

	ft_putstr(RESET);
	ft_putstr(" $> ");
}

// avec multicommand

int		main(int ac, char **av, char **environ)
{
	char	*line;
	t_com	*todo;
	t_com	*start;
	int		status;
	pid_t	new;
	char	**env;

	(void)ac;
	(void)av;
	
	// copier l'env pour pouvoir le modifier
	if (!(env = ft_tabdup(environ)))
		ft_exit("unable to malloc env", 1);
	line = NULL;

	// augmenter le SHLVL

	while (1)
	{
		status = 0;
		display_prompt(env);
		if (get_next_line(0, &line) != 1)
			ft_exit("GNL error", 1);
		// parsing


		todo = read_userinput(line);
		
		ft_strdel(&line);

		if (!todo)
			continue ;
		// start : buildin ou commande ?
		start = todo;
		while (todo)
		{
			if (todo->builtin == CD)
				builtin_cd(todo, &env);
			else if (todo->builtin == ECHO)
				builtin_echo(todo);
			else if (todo->builtin == ENV)
				builtin_env(todo, &env);
			else if (todo->builtin == EXIT)
				builtin_exit(todo);
			else if (todo->builtin == SETENV)
				builtin_setenv(todo, &env);
			else if (todo->builtin == UNSETENV)
				builtin_unsetenv(todo, &env);
			// execution
			else if (launch_command(todo, env))
			{
				if ((new = fork()) == -1)
					ft_exit("Fork failed", 1);
				else if (new == 0)
				{
					ft_putendl("-----------");
					status = execve(todo->path, todo->command, env);
					ft_putnbr_endl(status);
				}
				else
				{
					wait(0);
					ft_putnbr_endl(status);
					ft_putendl("fin");
				}
			}

			// verif si mauvais parsing
			if (status == -1)
				ft_exit("Kill ghost processus", 1);
			todo=todo->next;
		}
		sh_lstdel(&start);
	}
	// free(line);
	return (0);
}

// sans multicommand

// int		main(int ac, char **av, char **environ)
// {
// 	char	*line;
// 	t_com	*todo;
// 	int		status;
// 	pid_t	new;
// 	char	**env;

// 	(void)ac;
// 	(void)av;
	
// 	// copier l'env pour pouvoir le modifier
// 	if (!(env = ft_tabdup(environ)))
// 		ft_exit("unable to malloc env", 1);

// 	while (1)
// 	{
// 		status = 0;
// 		ft_putstr("$> ");
// 		get_next_line(0, &line);
// 		// parsing

// 		todo = read_userinput(line);
		
// 		ft_strdel(&line);
		
// 		if (!todo)
// 			continue ;
// 		// start : buildin ou commande ?
// 		if (todo->builtin == CD)
// 			ft_putendl("---> cd a venir");
// 		else if (todo->builtin == ECHO)
// 			builtin_echo(todo);
// 		else if (todo->builtin == ENV)
// 			builtin_env(todo, &env);
// 		else if (todo->builtin == EXIT)
// 			builtin_exit(todo);
// 		else if (todo->builtin == SETENV)
// 			builtin_setenv(todo, &env);
// 		else if (todo->builtin == UNSETENV)
// 			builtin_unsetenv(todo, &env);

// 		// execution
// 		else if ((new = fork()) == -1)
// 			ft_exit("Fork failed", 1);
// 		else if (new == 0)
// 		{
// 			ft_putendl("-----------");
// 			status = execve(todo->path, todo->command, env);
// 			ft_putnbr_endl(status);
// 		}
// 		else
// 		{
// 			wait(0);
// 			ft_putnbr_endl(status);
// 			ft_putendl("fin");
// 		}
		
// 		// verif si mauvais parsing
// 		if (status == -1)
// 			ft_exit("Kill ghost processus", 1);

// 		sh_lstdel(&todo);

// 		// ft_freetab(&todo);

// 	}
// 	return (0);
// }

// avec multicommand -- version bof, pas de boucle inf

// int		main(void)
// {
// 	char	*line;
// 	char	**input;
// 	char	**tab;
// 	char	**temp;
// 	t_com	*user;
// 	t_com	*elem;
// 	int		status;
// 	pid_t	new;

// 	ft_putstr("$> ");
// 	ft_putnbr_endl(get_next_line(0, &line));

// 	input = ft_strsplit(line, ';');
// 	if (!input)
// 		return (1);
// 	ft_puttab(input);

// 	temp = input;
// 	while (*temp)
// 	{
// 		tab = ft_strsplit(*temp, ' ');
// 		elem = sh_lstnew(tab);
// 		sh_lstaddlast(&user, elem);
// 		free(tab);
// 		temp++;
// 	}
	
// 	status = 0;

// 	while (user)
// 	{
// 		if ((new = fork()) == -1)
// 			ft_exit("Fork failed", 1);
// 		else if (new == 0)
// 		{
// 			ft_putendl("-----------");
// 			status = execve(user->path, user->command, NULL);
// 			ft_putnbr_endl(status);

// 		}
// 		else
// 		{
// 			wait(0);
// 			ft_putendl(user->path);
// 			ft_putnbr_endl(status);
// 			ft_putendl("fin");
// 		}
// 		user = user->next;
// 	}
// 	return (0);
// }