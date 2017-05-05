/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:21:08 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/05 20:34:48 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void (*signal(int sig, void (*handler)(int)))(int)

void		ft_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr("signal capte");
		write(1, "\n", 1);
		display_prompt();
	}
}

// SIGABRT abnormal termination, e.g., from abort
// SIGFPE arithmetic error, e.g., zero divide or overflow
// SIGILL illegal function image, e.g., illegal instruction
// SIGINT interactive attention, e.g., interrupt
// SIGSEGV illegal storage access, e.g., access outside memory limits 
// SIGTERM termination request sent to this program
