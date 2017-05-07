/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:21:08 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/07 22:24:21 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_handler_father(int sig)
{
	// write(1, "father", 7);

	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		display_prompt();
	}
}

void		ft_handler_child(int sig)
{
	// write(1, "child", 6);

	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		kill(SIGCHLD, SIGINT);
	}
}
