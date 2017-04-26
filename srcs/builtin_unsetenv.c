/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 09:32:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/26 18:28:02 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unsetenv(t_com *input, char ***env)
{
	char	**new;
	char	**old;
	int		len;
	int		i;
	int		j;

	len = count_var_suppr(input, env);
	if (!(new = (char**)malloc(sizeof(char*) * (len + 1))))
		ft_exit("Unable to malloc env", 1);
	*(new + len) = 0;
	i = 0;
	j = 0;
	while (*(*env + j) && i < len)
	{
		if (check_var_suppr(input, *(*env + j)))
		{
			free(*(*env + j));
			j++;
		}
		else
			*(new + i++) = *(*env + j++);
	}
	old = *env;
	*env = new;
	free(old);
}

int		count_var_suppr(t_com *input, char ***env)
{
	int	len;
	int	i;
	int	j;

	len = ft_tablen(*env);
	i = 1;
	while (input->command[i])
	{
		j = 0;
		while (*(*env + j))
		{
			if ((ft_strncmp(input->command[i], *(*env + j),\
				ft_strchr(*(*env + j), '=') - *(*env + j))) == 0)
				len--;
			j++;
		}
		i++;
	}
	return (len);
}

int		check_var_suppr(t_com *input, char *env)
{
	int	i;

	i = 1;
	while (input->command[i])
	{
		if ((ft_strncmp(input->command[i], env,\
			ft_strchr(env, '=') - env)) == 0)
			return (1);
		i++;
	}
	return (0);
}
