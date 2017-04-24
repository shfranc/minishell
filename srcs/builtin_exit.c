/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:05:19 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/24 17:02:30 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_com *input)
{
	ft_putendl_fd("exit", 2);
	if (!*(input->command + 1))
		exit(0);
	else if (!(ft_isnumber(*(input->command + 1))))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(*(input->command + 1), 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(255);
	}
	else if (*(input->command + 2))
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	else
		exit(ft_atoi(*(input->command + 1)));
}
