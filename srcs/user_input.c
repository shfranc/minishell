/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:32:27 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/19 19:14:08 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **read_userinput(char **line)
{
	char	**input;
	char	*temp;
	int		i;

	temp = *line;
	*line = ft_strtrim(*line);
	free(temp);
	if (!**line)
		return (NULL);

	ft_putstr(*line);
	ft_putendl("*");

	input = ft_strsplit(*line, ' ');

	i = 0;
	while (input[i])
	{
		temp = input[i];
		input[i] = ft_strtrim(input[i]);
		free(temp);
		i++;
	}

	ft_puttab(input);
	ft_putendl("**");

	return (input);
}