/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:55:07 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/19 18:54:49 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sans multicommand

int		main(void)
{
	char	*line;
	char	**input;
	int		status;
	pid_t	new;

	while (1)
	{
		status = 0;
		ft_putstr("$> ");
		get_next_line(0, &line);
		// parsing

		input = read_userinput(&line);
		if (!input)
			continue ;
		
		// start : buildin ou commande ?
		if (ft_strequ(*input, "exit"))
			builtin_exit(status);

		// execution
		if ((new = fork()) == -1)
			ft_exit("Fork failed", 1);
		else if (new == 0)
		{
			ft_putendl("-----------");
			status = execve(*input, input, NULL);
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

		ft_freetab(&input);
		ft_strdel(&line);
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