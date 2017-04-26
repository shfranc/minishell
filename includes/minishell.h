/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 10:07:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/26 12:16:08 by sfranc           ###   ########.fr       */
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
**	Read user input
*/
t_com 	*read_userinput(char *line);
char	**split_command(char *s);
void	ft_addtotab(char ***tab, char *add);
void	is_builtin(t_com *elem);

/*
**	Built-in echo
*/
void	builtin_echo(t_com *input);

/*
**	Built-in env
*/
void	builtin_env(t_com *input, char ***env);

/*
**	Built-in exit
*/
void	builtin_exit(t_com	*input);

/*
**	Built-in setenv
*/
void	builtin_setenv(t_com *input, char ***env);
int		parsing_setenv(t_com *input, char **temp);
int		modify_variable(char *name, char ***env);
void	adding_variable(char *name, char ***env);

/*
**	Built-in unsetenv
*/
void	builtin_unsetenv(t_com *input, char ***env);
int		count_var_suppr(t_com *input, char ***env);
int		check_var_suppr(t_com *input, char *env);

/*
**	Listes minishell
*/
t_com	*sh_lstnew(char **tab);
void	sh_lstaddlast(t_com **head, t_com *new);
void	sh_lstdel(t_com **head);

#endif