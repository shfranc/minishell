/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 10:41:23 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/05 14:51:12 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int		launch_command(t_com *input, char **env)
{
	char			**path;
	char			*error;

	if (!*input->path)
		return (display_cmd_err(input, ": command not found"));
	error = NULL;
	if (ft_strchr(input->path, '/'))
		return (check_existing_path(input));
	if ((path = get_path_variable(env)))
	{
		search_through_path(input, path, &error);
		ft_freetab(&path);
		if (error)
		{
			display_cmd_err(input, error);
			free(error);
			return (0);
		}
		else
			return (1);
	}
	else
		return (display_cmd_err(input, ": command not found"));
}

int		check_existing_path(t_com *input)
{
	char		*temp;
	struct stat	tmp_stat;
	int			ret;

	if ((ret = stat(input->path, &tmp_stat)) != -1)
	{
		if (S_ISDIR(tmp_stat.st_mode))
			return (display_cmd_err(input, ": is a directory"));
		else if ((tmp_stat.st_mode & S_IXUSR) != S_IXUSR)
			return (display_cmd_err(input, ": Permission denied"));
		else
			return (1);
	}
	else if (*(input->path + ft_strlen(input->path) - 1) == '/')
	{
		temp = ft_strsub(input->path, 0, ft_strlen(input->path) - 1);
		ret = stat(temp, &tmp_stat);
		free(temp);
		return (ret != -1 ? display_cmd_err(input, ": Not a directory") :\
			display_cmd_err(input, ": No such file or directory"));
	}
	else
		return (display_cmd_err(input, ": No such file or directory"));
}

void	search_through_path(t_com *input, char **path, char **error)
{
	struct stat	tmp_stat;
	char		*test;
	int			ret;
	int			i;

	i = 0;
	while (*(path + i))
	{
		test = ft_strjoin3(*(path + i), "/", input->path);
		if ((ret = stat(test, &tmp_stat)) != -1)
		{
			if ((tmp_stat.st_mode & S_IXUSR) != S_IXUSR)
				*error = ft_strdup(": Permission denied");
			else
			{
				free(input->path);
				input->path = ft_strdup(test);
				free(test);
				break ;
			}
		}
		free(test);
		++i;
	}
	ret == -1 ? *error = ft_strdup(": command not found") : 0;
}

char	**get_path_variable(char **env)
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
	return (NULL);
}

int		display_cmd_err(t_com *input, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(input->path, 2);
	ft_putendl_fd(error, 2);
	return (0);
}
