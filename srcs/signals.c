/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:21:08 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/08 10:54:30 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_handler_father(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		ft_display_prompt();
	}
}

void		ft_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		if (wait(0))
			write(1, "\n", 1);
		kill(SIGCHLD, SIGINT);
	}
}
