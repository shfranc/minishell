/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beginning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:13:20 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/08 11:10:31 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_increase_shlvl(char ***env)
{
	char	*shlvl;
	char	*temp;
	char	*newlvl;
	int		lvl;

	if ((shlvl = ft_get_env_variable(*env, "SHLVL=")))
	{
		lvl = ft_atoi(shlvl) + 1;
		newlvl = ft_itoa(lvl);
		temp = shlvl;
		shlvl = ft_strjoin("SHLVL=", newlvl);
		free(temp);
		free(newlvl);
		ft_modify_variable(env, shlvl);
		free(shlvl);
	}
	else
		ft_addtotab(env, "SHLVL=1");
}

void	ft_update_pwd(char ***env)
{
	char	*cwd;
	char	*pwd;
	char	*temp;

	if (!(cwd = getcwd(NULL, 0)))
		return ;
	if ((pwd = ft_get_env_variable(*env, "PWD=")))
	{
		temp = cwd;
		cwd = ft_strjoin("PWD=", cwd);
		free(temp);
		ft_modify_variable(env, cwd);
		free(pwd);
		free(cwd);
	}
	else
	{
		pwd = ft_strjoin("PWD=", cwd);
		ft_addtotab(env, pwd);
		free(pwd);
		free(cwd);
	}
}

void	ft_display_prompt(void)
{
	char *user;
	char *cwd;

	user = NULL;
	cwd = NULL;
	ft_putstr(BCYAN);
	if ((user = getlogin()))
	{
		ft_putstr(user);
		ft_putstr(": ");
	}
	else
		ft_putstr("minishell: ");
	ft_putstr(RESET);
	ft_putstr(BBLUE);
	if ((cwd = getcwd(NULL, 0)))
		ft_putstr(cwd);
	free(cwd);
	ft_putstr(RESET);
	ft_putstr(" $> ");
}
