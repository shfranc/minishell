/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 09:32:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/12 14:12:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_unsetenv(t_com *input, char ***env)
{
	int	i;
	int suppr;

	i = 1;
	while (*(input->command + i))
	{
		if ((suppr = ft_isinenv(*env, *(input->command + i))) == -1)
		{
			i++;
			continue ;
		}
		ft_supprtotab(env, suppr);
		i++;
	}
}

int		ft_isinenv(char **env, char *var)
{
	char	*temp;
	int		i;
	int		ret;

	i = 0;
	ret = -1;
	while (*(env + i))
	{
		temp = ft_strsub(*(env + i), 0,\
			ft_strchr(*(env + i), '=') - *(env + i));
		if (ft_strequ(temp, var))
			ret = i;
		i++;
		free(temp);
	}
	return (ret);
}
