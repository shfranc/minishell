/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:45:33 by exam              #+#    #+#             */
/*   Updated: 2017/05/03 15:04:20 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		value_size(int value, int base)
{
	int	size;

	size = 0;
	if (base <= 1 || base >= 17)
		return (0);
	if (value < 0 && base == 10)
		size++;
	if (value == 0)
		size++;
	while (value != 0)
	{
		size++;
		value /= base;
	}
	return (size);
}

char			*ft_itoa_base(int value, int base)
{
	static char	tab[16] = "0123456789ABCDEF";
	char		*result;
	int			size;
	long		nb;

	if (!(size = value_size(value, base)))
		return (0);
	if (!(result = (char *)malloc(sizeof(char) * (size + 1))))
		ft_exit("Unable to malloc", 2);
	result[size] = '\0';
	if (value == 0)
		result[0] = '0';
	if (value < 0 && base == 10)
		result[0] = '-';
	nb = (long)value;
	if (nb < 0)
		nb = nb * -1;
	while (nb != 0 && size--)
	{
		result[size] = tab[nb % base];
		nb /= base;
	}
	return (result);
}
