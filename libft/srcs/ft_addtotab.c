/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addtotab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:57:36 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/26 14:58:43 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_addtotab(char ***tab, char *add)
{
	char	**new;
	char	**old;
	int		len;
	int		i;

	if (*tab)
		len = ft_tablen(*tab) + 1;
	else
		len = 1;
	if (!(new = (char**)malloc(sizeof(char*) * (len + 1))))
		ft_exit("Unable to malloc", 1);
	*(new + len) = 0;
	i = 0;
	while (*tab && *(*tab + i))
	{
		*(new + i) = *(*tab + i);
		i++;
	}
	*(new + i) = ft_strdup(add);
	old = *tab;
	*tab = new;
	free(old);
}
