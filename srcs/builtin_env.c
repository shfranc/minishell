/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:55:08 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/21 18:28:38 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**save_env(char ***environ)
{
	char **env;
	int len;
	int	i;

	len = ft_tablen(*environ);
	if (!(env = (char**)malloc(sizeof(char*) * (len + 1))))
		ft_exit("Unable to malloc env", 1);
	*(env + len) = 0;
	i = 0;
	while (i < len)
	{
		*(env + i) = ft_strdup(*(*environ + i));
		i++;
	}
	// ft_puttab(env);
	// ft_putnbr_endl(len);
	return (env);
}

void	**builtin_env(t_com *input, char **env)
{
	(void)input;
	// char	**new;
	// char	**begin;

	if (!*(input->command + 1))
		ft_puttab(env);
	// else if (ft_strequ(*(input->command + 1), "-i"))
	// {
	// 	faire un nouvel env et le rendre ? mais il ne doit etre utiliser qu'une seule fois...
	// }
	else
		return ;
}