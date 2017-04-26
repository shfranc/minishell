/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 19:23:38 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/26 19:26:49 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		move_endofarg(char *s)
{
	int len;

	len = 0;
	while (*(s + len) && !ft_isspace(*(s + len)))
	{
		if (*(s + len) && *(s + len) == '"')
		{
			len++;
			while (*(s + len) && *(s + len) != '"')
				len++;
		}
		if (*(s + len))
			len++;
	}
	return (len);
}

char	*strsub_withoutquotes(char *s, int len)
{
	char *begin;
	char *new;
	int len_less;

	len_less = len - nb_quotes(s, len);
	if (!(new = ft_strnew(len_less)))
		ft_exit("Unable to malloc", 1);
	begin = new;
	while (*s && len--)
	{
		if (*s != '"')
			*new++ = *s++;
		else
			s++;
	}
	return (begin);
}

int		nb_quotes(char *s, int len)
{
	int quotes;

	quotes = 0;
	while (*s && len--)
	{
		if (*s == '"')
			quotes++;
		s++;
	}
	return (quotes);

}
