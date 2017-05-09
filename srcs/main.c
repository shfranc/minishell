/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:55:07 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/09 11:19:53 by sfranc           ###   ########.fr       */
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
	env = ft_tabdup(environ);
	ft_update_pwd(&env);
	ft_increase_shlvl(&env);
	while (1)
	{
		if (signal(SIGINT, ft_handler_father) == SIG_ERR)
			ft_exit("minishell: unable to catch the signal", 1);
		ft_display_prompt();
		if (get_next_line(0, &line) != 1)
			ft_exit("exit", 0);
		todo = ft_read_userinput(line);
		ft_strdel(&line);
		if (!todo)
			continue ;
		ft_execute_command(todo, &env);
		ft_sh_lstdel(&todo);
	}
	return (0);
}
