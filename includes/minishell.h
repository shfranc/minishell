/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 10:07:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/21 16:14:21 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <signal.h>


# define CD			1
# define ECHO		1 << 1
# define ENV		1 << 2
# define EXIT		1 << 3
# define SETENV 	1 << 4
# define UNSETENV	1 << 5

typedef struct	s_command
{
	char				*path;
	char				**command;
	int					builtin;
	int					error;
	char				*status;
	struct s_command	*next;
}
				t_com;

/*
**	Listes minishell
*/
t_com	*sh_lstnew(char **tab);
void	sh_lstaddlast(t_com **head, t_com *new);
void	sh_lstdel(t_com **head);

/*
**	Built-in echo
*/
void	builtin_echo(t_com *input);

/*
**	Built-in exit
*/
char	**save_env(char ***environ);
void	builtin_env(t_com *input, char **env);

/*
**	Built-in exit
*/
void	builtin_exit(t_com	*input);

/*
**	Read user input
*/
t_com 	*read_userinput(char **line);
void	is_builtin(t_com *elem);

#endif