/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_supprtotab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 11:22:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/12 11:24:03 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_supprtotab(char ***tab, int suppr)
{
	char	**new;
	char	**old;
	int		len;
	int		i;
	int		j;

	len = ft_tablen(*tab) - 1;
	if (!(new = (char**)malloc(sizeof(char*) * (len + 1))))
		ft_exit("Unable to malloc tab", 1);
	*(new + len) = 0;
	i = 0;
	j = 0;
	while (*(*tab + j))
	{
		if (j != suppr)
			*(new + i++) = *(*tab + j++);
		else
			free(*(*tab + j++));
	}
	old = *tab;
	*tab = new;
	free(old);
}
