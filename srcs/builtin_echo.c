/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 15:31:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/08 11:08:46 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_echo(t_com *input)
{
	int	i;
	int n;

	n = 0;
	i = 1;
	if (ft_strequ(*(input->command + 1), "-n"))
	{
		n = 1;
		i++;
	}
	while (*(input->command + i))
	{
		ft_putstr(*(input->command + i));
		if (*(input->command + ++i))
			write(1, " ", 1);
	}
	if (n == 0)
		write(1, "\n", 1);
}
