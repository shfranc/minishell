/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:55:08 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/12 14:13:19 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_env(t_com *input, char ***env)
{
	if (!*(input->command + 1))
		ft_puttab(*env);
}

char	*ft_get_env_variable(char **env, char *var)
{
	char	*temp;
	char	*stop;
	int		i;

	i = 0;
	while (*(env + i))
	{
		temp = ft_strsub(*(env + i), 0,\
			ft_strchr(*(env + i), '=') - *(env + i));
		if (ft_strequ(temp, var))
		{
			stop = ft_strchr(*(env + i), '=');
			free(temp);
			return (ft_strsub(*(env + i), stop - *(env + i) + 1,\
				ft_strlen(stop)));
		}
		i++;
		free(temp);
	}
	return (NULL);
}

void	ft_change_pwd(char **pwd, char ***env)
{
	char	*temp;

	temp = ft_strjoin("PWD=", *pwd);
	if (!ft_modify_variable(env, temp))
		ft_addtotab(env, temp);
	free(temp);
	ft_strdel(pwd);
}

void	ft_change_oldpwd(char **old_pwd, char ***env)
{
	char *temp;

	temp = ft_strjoin("OLDPWD=", *old_pwd);
	if (!ft_modify_variable(env, temp))
		ft_addtotab(env, temp);
	free(temp);
	ft_strdel(old_pwd);
}

void	ft_builtin_printenv(t_com *input, char ***env)
{
	char *temp;

	temp = NULL;
	if (!*(input->command + 1))
		ft_puttab(*env);
	else if ((temp = ft_get_env_variable(*env, *(input->command + 1))))
	{
		ft_putendl(temp);
		free(temp);
	}
}
