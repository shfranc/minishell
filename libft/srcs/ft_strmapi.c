/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 13:40:10 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/03 12:58:04 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_s;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (!(new_s = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		ft_exit("Unable to malloc", 1);
	i = 0;
	while (*s)
	{
		*(new_s + i) = f(i, *s++);
		i++;
	}
	*(new_s + i) = '\0';
	return (new_s);
}
