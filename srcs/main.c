/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:55:07 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/05 20:31:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **environ)
{
	char	*line;
	t_com	*todo;
	char	**env;

	(void)ac;
	(void)av;
	line = NULL;
	// possible de grouper ces 3 actions dans une fonction start..
	env = ft_tabdup(environ);
	update_pwd(&env);
	increase_shlvl(&env);
	
	
	while (1)
	{	

		if (signal(SIGINT, ft_handler) == SIG_ERR)
			ft_exit("minishell: unable to catch the signal", 1);
		
		display_prompt();
		
		if (get_next_line(0, &line) != 1)
			ft_exit("exit", 0);
		todo = read_userinput(line);
		ft_strdel(&line);
		if (!todo)
			continue ;
		execute_command(todo, &env);
	}
	return (0);
}
