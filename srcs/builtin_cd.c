/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:06:02 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/12 12:49:58 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_cd(t_com *input, char ***env)
{
	char	*old_pwd;
	char	*temp;

	if (!*(input->command + 1))
	{
		ft_move_to_home(env);
		return ;
	}
	if (!ft_fetch_oldpwd(input, *env))
		return ;
	if (!(old_pwd = getcwd(NULL, 0)))
		old_pwd = NULL;
	if ((chdir(*(input->command + 1))) != -1)
	{
		if ((temp = getcwd(NULL, 0)))
			ft_change_pwd(&temp, env);
		free(temp);
		if (old_pwd)
			ft_change_oldpwd(&old_pwd, env);
	}
	else
	{
		free(old_pwd);
		ft_display_cd_err(*(input->command + 1));
	}
}

int		ft_fetch_oldpwd(t_com *input, char **env)
{
	if (ft_strequ(*(input->command + 1), "-"))
	{
		free(*(input->command + 1));
		*(input->command + 1) = ft_get_env_variable(env, "OLDPWD");
		if (!*(input->command + 1))
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (0);
		}
		else
		{
			if (access(*(input->command + 1), X_OK) != -1)
				ft_putendl(*(input->command + 1));
		}
	}
	return (1);
}

void	ft_move_to_home(char ***env)
{
	char		*old_pwd;
	char		*pwd;

	if ((pwd = ft_get_env_variable(*env, "HOME")))
	{
		if (!(old_pwd = getcwd(NULL, 0)))
			;
		if ((chdir(pwd)) != -1)
		{
			ft_change_pwd(&pwd, env);
			if (old_pwd)
				ft_change_oldpwd(&old_pwd, env);
		}
		else
		{
			free(old_pwd);
			ft_display_cd_err(pwd);
			free(pwd);
		}
	}
	else
		ft_putendl_fd("minishell: cd: HOME not set", 2);
}

void	ft_display_cd_err(char *pwd)
{
	struct stat	pwd_stat;

	if ((stat(pwd, &pwd_stat)) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(pwd, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (!S_ISDIR(pwd_stat.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(pwd, 2);
		ft_putendl_fd(": Not a directory", 2);
	}
	else if (access(pwd, X_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(pwd, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
}
