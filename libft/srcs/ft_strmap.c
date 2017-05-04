/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:08:57 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/03 14:09:40 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new_s;
	int		i;

	if (!s)
		return (NULL);
	if (!(new_s = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		ft_exit("Unable to malloc", 1);
	i = 0;
	while (*s)
		*(new_s + i++) = f(*s++);
	*(new_s + i) = '\0';
	return (new_s);
}
