/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 09:32:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/28 17:39:05 by sfranc           ###   ########.fr       */
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
			ft_putendl(*(*env + j));
			free(*(*env + j));
			j++;
		}
		else
			*(new + i++) = *(*env + j++);
	}
	if (*(*env + j) && ft_strequ(*(new + i), *(*env + j)))
	{
		ft_putendl("free la derniere ligne");
		free(*(*env + j));
	}
	// ft_putendl(*(*env + j));
	old = *env;
	*env = new;
	free(old);
}

int		count_var_suppr(t_com *input, char ***env)
{
	char *temp;
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
			temp = ft_strsub(*(*env + j), 0, ft_strchr(*(*env + j), '=') - *(*env + j));
			if(ft_strequ(temp, input->command[i]))
				len--;
			free(temp);
			j++;
		}
		i++;
	}
	return (len);
}

int		check_var_suppr(t_com *input, char *env)
{
	char *temp;
	int	i;

	i = 1;
	while (input->command[i])
	{
		temp = ft_strsub(env, 0, ft_strchr(env, '=') - env);
		if(ft_strequ(temp, input->command[i]))
		{
			free(temp);
			return (1);
		}
		free(temp);
		i++;
	}
	return (0);
}
