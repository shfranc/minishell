/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:55:07 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/18 17:56:33 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(void)
{
	char	*line;
	t_user	user;
	t_list	*elem;
	t_list	*to_do;
	char	**input;
	char	**temp;
	t_list	*tmp;
	// char	**user;
	// char	*user_command;
	// int		ret;

	ft_putstr("$> ");
	ft_putnbr_endl(get_next_line(0, &line));
		// ft_exit("test", 0);
	input = ft_strsplit(line, ';');
	if (!input)
		return (1);
	ft_puttab(input);
	to_do = NULL;
	temp = input;
	while (*temp)
	{
		user.command = ft_strsplit(*temp, ' ');
		user.path = ft_strdup(*user.command);
		user.status = 0;
		elem = ft_lstnew(&user, sizeof(user));
		// ft_lstadd_last(&to_do, elem);
		temp++;
	}

	tmp = to_do;
	while (tmp)
	{
		ft_putendl("---------");
		ft_putendl(((t_user*)(tmp->content))->path);
		ft_puttab(((t_user*)(tmp->content))->command);
		ft_putnbr_endl(((t_user*)(tmp->content))->status);
		tmp=tmp->next;
	}


	

	// ft_putendl(to_do->content.user.command);

	// while (to_do)
	// {
	// 	ft_putendl(to_do->content.user.command);
	// 	to_do = to_do->next;
	// }

	// ft_putstr("$> ");

	// ft_puttab(tab);

	// user = ft_strsplit(*tab, ' ');
	
	// ft_puttab(user);

	// user_command = *user;
	// *user = ft_strrchr(*user, '/') + 1;
	// ft_putstr("command : ");
	
	// ft_putstr("arguments : ");
	

	// ft_putendl("-----------");
	
	// ret = execve(user_command, user, NULL);

	// ft_putnbr_endl(ret);
	// ft_putendl("fin");

	return (0);
}