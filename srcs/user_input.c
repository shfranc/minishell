/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:32:27 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/26 13:07:44 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <errno.h>
#include <stdio.h>

t_com 	*read_userinput(char *line)
{
	char **command;

	command = split_command(line);

	
	return (NULL);
}

char	**split_command(char *s)
{
	char	*begin;
	char	**command;
	int		start;
	int		len;
	int 	check;
	char 	*temp;
	
	if (*s && *s == ';')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
		return (NULL);
	}

	command = NULL;
	begin = s;
	start = 0;
	len = 0;
	check = 0;

	while (*s)
	{
		if (*s && *s != ';')
		{
			check = 0;
			len = 0;
			while (*s && *s != ';')
			{
				if (*s && *s == '"')
				{
					len++;
					s++;
					while (*s && *s != '"')
					{
						len++;
						s++;
					}
				}
				if (*s)
				{
					len++;
					s++;
				}
			}
			temp = ft_strsub(begin, start, len);
			ft_addtotab(&command, temp);
			free(temp);
			start += len;
		}


		else if (*s && *s == ';')
		{
			s++;
			start++;
			check++;
		}
		if (check > 1)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `;;'", 2);
			return (NULL);
		}
	}
	ft_puttab(command);
	return (command);
}

void	ft_addtotab(char ***tab, char *add)
{
	char	**new;
	char	**old;
	int 	len;
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

void	is_builtin(t_com *elem)
{
	char	**builtin;
	int		i;
	char	*test;

	test = ft_strdup("cd echo env exit setenv unsetenv");
	builtin = ft_strsplit(test, ' ');
	free(test);
	i = 0;
	while (i < 6)
	{
		if (ft_strequ(elem->path, *(builtin + i)))
			elem->builtin = 1 << i;
		++i;
	}
	ft_freetab(&builtin);
}

char	**split_command(char *s)
{
	char	*begin;
	char	**command;
	int		start;
	int		len;
	int 	check;
	char 	*temp;
	
	if (*s && *s == ';')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
		return (NULL);
	}

	command = NULL;
	begin = s;
	start = 0;
	len = 0;
	check = 0;

	while (*s)
	{
		if (*s && *s != ';')
		{
			check = 0;
			len = 0;
			while (*(s + len) && *(s +len) != ';')
			{
				if (*(s + len) && *(s + len) == '"')
				{
					len++;
					// s++;
					while (*(s + len) && *(s + len) != '"')
					{
						len++;
						// s++;
					}
				}
				if (*(s + len))
				{
					len++;
					// s++;
				}
			}
			temp = ft_strsub(begin, start, len);
			ft_addtotab(&command, temp);
			free(temp);
			start += len;
			s = s + len;
		}


		else if (*s && *s == ';')
		{
			s++;
			start++;
			check++;
		}
		if (check > 1)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `;;'", 2);
			return (NULL);
		}
	}
	ft_puttab(command);
	return (command);
}

// char	**split_command(char *s)
// {
// 	char	*begin;
// 	char	**command;
// 	int		start;
// 	int		len;
// 	int 	check;
// 	char 	*temp;
	
// 	if (*s && *s == ';')
// 	{
// 		ft_putendl_fd("minishell: syntax error near unexpected token `;'", 2);
// 		return (NULL);
// 	}

// 	command = NULL;
// 	begin = s;
// 	start = 0;
// 	len = 0;
// 	check = 0;

// 	while (*s)
// 	{
// 		if (*s && *s != ';')
// 		{
// 			check = 0;
// 			len = 0;
// 			while (*s && *s != ';')
// 			{
// 				if (*s && *s == '"')
// 				{
// 					len++;
// 					s++;
// 					while (*s && *s != '"')
// 					{
// 						len++;
// 						s++;
// 					}
// 				}
// 				if (*s)
// 				{
// 					len++;
// 					s++;
// 				}
// 			}
// 			temp = ft_strsub(begin, start, len);
// 			ft_addtotab(&command, temp);
// 			free(temp);
// 			start += len;
// 		}


// 		else if (*s && *s == ';')
// 		{
// 			s++;
// 			start++;
// 			check++;
// 		}
// 		if (check > 1)
// 		{
// 			ft_putendl_fd("minishell: syntax error near unexpected token `;;'", 2);
// 			return (NULL);
// 		}
// 	}
// 	ft_puttab(command);
// 	return (command);
// }

// void	draft_line(char *line)
// {
// 	int i;
// 	int j;
// 	int command;


// 	if (line[0] == ';' && !line[1])
// 	{
// 		ft_putendl_fd("minishell: syntax error near ';'", 2);
// 		return ;
// 	}

// 	if (line[0] == ';' && line[1] == ';')
// 	{
// 		ft_putendl_fd("minishell: syntax error near ';;'", 2);
// 		return ;
// 	}

// 	command = 0;
// 	j = 0;
// 	while (line[j])
// 	{
// 		ft_putendl(line + j);
// 		if (line[i] != ';')
// 		{
// 			command++;
// 			i = j;
// 			while (line[i] && line[i] != ';')
// 			{
// 				if (line[i] == '"')
// 				{
// 					i++;
// 					while (line[i] && line[i] != '"')
// 						i++;
// 				}
// 				if (line[i])
// 					i++;
// 			}
// 		}
// 		if (line[i])
// 			j = i;
// 	}
// }

// t_com 	*read_userinput(char *line)
// {
// 	t_com	*elem;
// 	char	**input;
// 	char	*temp;
// 	// int		i;


// 	temp = *line;
// 	*line = ft_strtrim(*line);
// 	free(temp);
// 	if (!**line)
// 		return (NULL);
// 	// ft_putstr(*line);
// 	// ft_putendl("*");

// 	input = ft_strsplit(*line, ' ');
// 	// i = 0;
// 	// while (input[i])
// 	// {
// 	// 	temp = input[i];
// 	// 	input[i] = ft_strtrim(input[i]);
// 	// 	free(temp);
// 	// 	i++;
// 	// }

// 	// ft_puttab(input);
// 	// ft_putendl("**");

// 	elem = sh_lstnew(input);

// 	ft_freetab(&input);
// 	is_builtin(elem);
// 	printbit(elem->builtin);

// 	if (!elem->builtin && access(elem->path, F_OK) == -1)
// 	{
// 		ft_putstr("==> ");
// 		perror(strerror(errno));
// 	}

// 	return (elem);
// }

// t_com 	*read_userinput(char *line)
// {	
// 	char	*begin;
// 	char	*end;
// 	char 	*command;

// 	command = NULL;
// 	begin = line;
// 	end = find_command(begin);
// 	if (end)
// 	{
// 		if (begin == end)
// 			ft_putendl_fd("minishell: syntax error near ';'", 2);
// 		else
// 			command = ft_strsub(begin, 0, end - begin);		
// 	}
// 	else
// 		command = ft_strdup(begin);

// 	if (command)
// 		ft_putendl(command);
// 	else
// 		ft_putendl("NULL");

// 	// while (begin)
// 	// {
		
		
// 	// 	command = ft_strsub(begin, 0, end - 1 - begin);
// 	// 	if (command)
// 	// 		ft_putendl(command);
// 	// 	else
// 	// 		ft_putendl("(null)");

// 	// 	if (*end == ';' && *(end + 1))
// 	// 		begin = end + 1;
// 	// 	else if (*end == 0)
// 	// 		begin = end;
// 	// }
// 	return (NULL);
// }

// char	*find_command(char *s)
// {
// 	char *find;

// 	find = ft_strchr(s, ';');
// 	return (find);
// }
