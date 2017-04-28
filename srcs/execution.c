/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 10:41:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/28 12:25:32 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	check_path(t_com *input, char **env)
{
	char			**path;
	char			*test;
	char			*temp;
	int				i;
	struct stat 	l_stat;
	int				ret;

	(void)env;

	if (!*input->path)
	{
		display_command_error(input);
		return (0);
	}

	if (access(input->path, F_OK) == 0)
	{
		ft_putendl("path OK ?");
		ret = lstat(input->path, &l_stat);
		if (S_ISDIR(l_stat.st_mode))
		{
			ft_putendl("is directory");
			return (0);
		}
		if (access(input->path, X_OK) == 0)
			return (1);
		else
		{
			ft_putendl("Permission denied");
			return (0);
		}
		return (1);
	}
	else
	{	
		// ft_putendl(strerror(errno));
		path = get_path_variable(env);
		i = 0;
		while (*(path + i))
		{
			test = ft_strjoin3(*(path + i), "/", input->path);
			// ft_putendl(test);
			if (access(test, F_OK) == 0)
			{
				ft_putendl("path trouve");
				temp = input->path;
				input->path = ft_strdup(test);
				free(temp);
				free(test);
				if (access(input->path, X_OK) == 0)
				{
					ft_freetab(&path);
					return (1);
				}
				else
				{
					ft_putendl("Permission denied");
					ft_freetab(&path);
					return (0);
				}
			}
			else
			{
				i++;
				free(test);
			}
		}
		if (i == ft_tablen(path))
			display_command_error(input);
		ft_freetab(&path);
	}
	return (0);
}

char **get_path_variable(char **env)
{
	char	**path;
	char	*temp;
	char	*find;
	int		i;

	i = 0;
	while (*(env + i))
	{
		if ((find = ft_strstr(*(env + i), "PATH=")))
		{
			temp = ft_strsub(find, 5, ft_strlen(find + 5));
			path = ft_strsplit(temp, ':');
			free(temp);
			return (path);
		}
		i++;
	}
	return (0);
}

void	display_command_error(t_com *input)
{
	if (!(ft_strchr(input->path, '/')))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->path, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->path, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

// bash: /bin/coco: No such file or directory
// bash: /bin/ls/: Not a directory
// bash: /bin: is a directory
// bash: lol: command not found
