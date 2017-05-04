/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 15:35:01 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/03 12:56:50 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew_set(size_t size, char c)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		ft_exit("Unable to malloc", 1);
	*(str + size) = 0;
	ft_memset(str, c, size);
	return (str);
}
