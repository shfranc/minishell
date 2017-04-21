/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:55:08 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/21 13:09:59 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_env(char ***environ, char ***env)
{
	int len;

	(void)env;
	(void)environ;
	len = 0;
	len = ft_tablen(environ);
	ft_puttab(*environ);
	ft_putnbr_endl(len);
}

// void	builtin_env(char **env);