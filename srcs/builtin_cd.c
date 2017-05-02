/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:58:16 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/02 14:30:51 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_com *input, char ***env)
{
	if (!*(input->command + 1))
		move_to_home(env);
}

void 	move_to_home(char ***env)
{
	char		*old_pwd;
	char		*pwd;
	struct stat	pwd_stat;

	if ((pwd = get_env_variable(*env, "HOME=")))
	{
		if (!(old_pwd = getcwd(NULL, 0)))
			;
		if ((chdir(pwd)) != -1)
		{
			change_pwd(&pwd, env);
			if (old_pwd)
				change_oldpwd(&old_pwd, env);
		}
		else
		{
			free(old_pwd);
			if ((stat(pwd, &pwd_stat)) == -1)
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd(pwd, 2);
				ft_putendl_fd(": No such file or directory", 2);
			}
			else if (!S_ISDIR(pwd_stat.st_mode))
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd(pwd, 2);
				ft_putendl_fd(": Not a directory", 2);
			}
			else if ((pwd_stat.st_mode & S_IXUSR) != S_IXUSR)
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd(pwd, 2);
				ft_putendl_fd(": Permission denied", 2);
			}
			free(pwd);
		}
	}
	else
		ft_putendl_fd("minishell: cd: HOME not set", 2);
}

void	change_pwd(char **pwd, char ***env)
{
	char	*temp;

	temp = ft_strjoin("PWD=", *pwd);
	modify_variable(temp, env);
	free(temp);
	ft_strdel(pwd);

}

void	change_oldpwd(char **old_pwd, char ***env)
{
	char *temp;

	temp = ft_strjoin("OLDPWD=", *old_pwd);
	modify_variable(temp, env);
	free(temp);
	ft_strdel(old_pwd);
}

char	*get_env_variable(char **env, char *var)
{
	char	*find;
	int		i;

	i = 0;
	while (*(env + i))
	{
		if ((find = ft_strstr(*(env + i), var)))
			return (ft_strsub(find, ft_strlen(var),\
				ft_strlen(find + ft_strlen(var))));
		i++;
	}
	return (NULL);
}
