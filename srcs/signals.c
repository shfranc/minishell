/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:21:08 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/08 13:30:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void		ft_handler_father(int sig)
{
	ft_putstr("father");
	// ft_putendl(getenv("test="));

	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_display_prompt();
	}
}

void		ft_handler_child(int sig)
{
	// ft_putstr("child");
	// ft_putendl(getenv("SHLVL="));

	if (sig == SIGINT)
	{
		if (kill(SIGCHLD, SIGINT) == -1)
		{
			ft_putstr("la");
			write(1, "\n", 1);
			// kill(SIGCHLD, SIGINT);
		}

		// if (wait(0) != -1)
		// {
		// 	write(1, "\n", 1);
		// 	kill(SIGCHLD, SIGINT);
		// }
		// else
		// {
		// 	ft_putendl(strerror(errno));
		// }
	}
}
