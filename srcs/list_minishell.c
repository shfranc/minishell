/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:51:41 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/27 18:53:05 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	*sh_lstnew(char **tab)
{
	t_com	*elem;

	if (!(elem = (t_com*)malloc(sizeof(t_com))))
		return (NULL);
	elem->path = ft_strdup(*tab);

	// ft_putendl(elem->path);

	elem->command = ft_tabdup(tab);

	// ft_puttab(elem->command);
	// ft_putendl("--- lst ---");

	elem->error = 0;
	elem->builtin = 0;
	elem->status = NULL;
	elem->next = NULL;
	return (elem);
}

void	sh_lstaddlast(t_com **head, t_com *new)
{
	t_com *temp;
	
	if (!head)
		return;
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

	if (!head)
		return;
	while ((*head)->next)
	{
		free((*head)->path);
		ft_freetab(&(*head)->command);
		free(*head);
		*head = (*head)->next;
	}
	free((*head)->path);
	ft_freetab(&(*head)->command);
	free(*head);
	*head = NULL;
}