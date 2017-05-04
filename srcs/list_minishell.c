/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:51:41 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/04 15:13:51 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	*sh_lstnew(char **tab)
{
	t_com	*elem;

	if (!(elem = (t_com*)malloc(sizeof(t_com))))
		ft_exit("Unable to malloc", 1);
	elem->path = ft_strdup(*tab);
	elem->command = ft_tabdup(tab);
	elem->builtin = 0;
	elem->next = NULL;
	return (elem);
}

void	sh_lstaddlast(t_com **head, t_com *new)
{
	t_com	*temp;

	if (!head)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	sh_lstdel(t_com **head)
{
	t_com *temp;
	t_com *prev;

	if (!head && !*head)
		return ;
	temp = *head;
	while (temp)
	{
		free(temp->path);
		ft_freetab(&temp->command);
		prev = temp;
		temp = temp->next;
		free(prev);
	}
}
