/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 13:09:59 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/03 14:05:52 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*begin;

	if (!lst || !f)
		return (NULL);
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		ft_exit("Unable to malloc", 1);
	new = f(lst);
	begin = new;
	lst = lst->next;
	while (lst)
	{
		if (!(new->next = (t_list*)malloc(sizeof(t_list))))
			ft_exit("Unable to malloc", 1);
		new->next = f(lst);
		new = new->next;
		lst = lst->next;
	}
	return (begin);
}
