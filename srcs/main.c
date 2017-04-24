/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:55:07 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/24 17:55:02 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sans multicommand

int		main(int ac, char **av, char **environ)
{
	char	*line;
	t_com	*input;
	int		status;
	pid_t	new;
	char	**env;

	(void)ac;
	(void)av;
	
	// copier l'env pour pouvoir le modifier
	if (!(env = ft_tabdup(environ)))
		ft_exit("unable to malloc env", 1);

	while (1)
	{
		status = 0;
		ft_putstr("$> ");
		get_next_line(0, &line);
		// parsing

		input = read_userinput(&line);
		ft_strdel(&line);		
		if (!input)
			continue ;
		
		// start : buildin ou commande ?
		if (input->builtin == CD)
			ft_putendl("---> cd a venir");
		else if (input->builtin == ECHO)
			builtin_echo(input);
		else if (input->builtin == ENV)
			builtin_env(input, &env);
		else if (input->builtin == EXIT)
			builtin_exit(input);
		else if (input->builtin == SETENV)
			builtin_setenv(input, &env);
		else if (input->builtin == UNSETENV)
			builtin_unsetenv(input, &env);

		// execution
		else if ((new = fork()) == -1)
			ft_exit("Fork failed", 1);
		else if (new == 0)
		{
			ft_putendl("-----------");
			status = execve(input->path, input->command, env);
			ft_putnbr_endl(status);
		}
		else
		{
			wait(0);
			ft_putnbr_endl(status);
			ft_putendl("fin");
		}
		
		// verif si mauvais parsing
		if (status == -1)
			ft_exit("Kill ghost processus", 1);

		sh_lstdel(&input);

		// ft_freetab(&input);

	}
	return (0);
}

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