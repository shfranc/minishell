/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 09:32:52 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/10 19:11:47 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_unsetenv(t_com *input, char ***env) // a refaire en entier !!!!!!!!
{
	char	**new;
	char	**old;
	int		len;
	int		i;
	int		j;
	int		k;

	len = 0;
	i = 1;
	while (*(input->command + i))
	{
		if (ft_exist_inenv(*env, *(input->command + i)))
		{
			ft_putendl("--------- exist");
			len = ft_tablen(*env) - 1;
			if (!(new = (char**)malloc(sizeof(char*) * (len + 1))))
				ft_exit("Unable to malloc env", 1);
			*(new + len) = 0;
			j = 0;
			k = 0;
			while (*(*env + j) && k < len)
			{
				if (ft_check_var_suppr(*(input->command + i), *(*env + j)))
				{
					ft_putendl("--------- suppr lui");
					free(*(*env + j++));
				}
				else
					*(new + k++) = *(*env + j++);
			}
			old = *env;
			*env = new;
			free(old);
			ft_putendl("--------- suppr OK");
			ft_puttab(*env);
		}
		ft_putendl("--------- next");
		++i;
	}
	ft_putendl("--------- DONE");
}

int		ft_exist_inenv(char **env, char *var)
{
	char	*test;

	if ((test = ft_get_env_variable(env, var)))
	{
		free(test);
		return (1);
	}
	return (0);
}

int		ft_check_var_suppr(char *input, char *env)
{
	char *temp;
	int ret;

	ret = 0;
	temp = ft_strsub(env, 0, ft_strchr(env, '=') - env);
	if (ft_strequ(temp, input))
		ret++;
	free(temp);
	return(ret);
}

// void	ft_builtin_unsetenv(t_com *input, char ***env)
// {
// 	char	**new;
// 	char	**old;
// 	int		len;
// 	int		i;
// 	int		j;

// 	len = ft_count_var_suppr(input, env);
// 	if (!(new = (char**)malloc(sizeof(char*) * (len + 1))))
// 		ft_exit("Unable to malloc env", 1);
// 	*(new + len) = 0;
// 	i = 0;
// 	j = 0;
// 	while (*(*env + j))
// 	{
// 		if (ft_check_var_suppr(input, *(*env + j)))
// 			free(*(*env + j++));
// 		else if (i < len)
// 			*(new + i++) = *(*env + j++);
// 	}
// 	old = *env;
// 	*env = new;
// 	free(old);
// }

// int		ft_count_var_suppr(t_com *input, char ***env)
// {
// 	char	*temp;
// 	int		len;
// 	int		i;
// 	int		j;

// 	len = ft_tablen(*env);
// 	i = 1;
// 	while (input->command[i])
// 	{
// 		j = 0;
// 		while (*(*env + j))
// 		{
// 			temp = ft_strsub(*(*env + j), 0,\
// 				ft_strchr(*(*env + j), '=') - *(*env + j));
// 			if (ft_strequ(temp, input->command[i]))
// 				len--;
// 			free(temp);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (len);
// }

// int		ft_check_var_suppr(t_com *input, char *env)
// {
// 	char	*temp;
// 	int		i;

// 	i = 1;
// 	while (input->command[i])
// 	{
// 		temp = ft_strsub(env, 0, ft_strchr(env, '=') - env);
// 		if (ft_strequ(temp, input->command[i]))
// 		{
// 			free(temp);
// 			return (1);
// 		}
// 		free(temp);
// 		i++;
// 	}
// 	return (0);
// }
