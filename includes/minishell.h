/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 10:07:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/02 13:40:46 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>

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
	struct s_command	*next;
}
				t_com;

/*
**	Read user input
*/
t_com 	*read_userinput(char *line);
char	**split_command(char *s);
int 	move_endofcommand(char *s);
int		beginwith_semicolon(char *s);
int		check_semicolon(int check, char ***command);

/*
**	Parse command
*/
t_com 	*parse_command(char **command);
char	**split_intoarg(char *s);
int		check_commandblank(char **command);
int		check_quotes(char **command);
void	is_builtin(t_com *elem);

/*
**	Parse command 2
*/
char	*strsub_withoutquotes(char *s, int len);
int		move_endofarg(char *s);
int		nb_quotes(char *s, int len);

/*
**	Execution
*/
int		launch_command(t_com *input, char **env);
int 	check_existing_path(t_com *input);
void	search_through_path(t_com *input, char **path, char **error);
char	**get_path_variable(char **env);
int		display_cmd_err(t_com *input, char *error);

/*
**	Bluitin cd
*/
void	builtin_cd(t_com *input, char ***env);
void 	move_to_home(char ***env);
void	change_pwd(char **pwd, char ***env);
void	change_oldpwd(char **old_pwd, char ***env);
char	*get_env_variable(char **env, char *var);

/*
**	Bluitin echo
*/
void	builtin_echo(t_com *input);

/*
**	Bluitin env
*/
void	builtin_env(t_com *vinput, char ***env);

/*
**	Bluitin exit
*/
void	builtin_exit(t_com	*input);

/*
**	Bluitin setenv
*/
void	builtin_setenv(t_com *input, char ***env);
int		parsing_setenv(t_com *input, char **temp);
int		modify_variable(char *var, char ***env);

/*
**	Bluitin unsetenv
*/
void	builtin_unsetenv(t_com *input, char ***env);
int		count_var_suppr(t_com *input, char ***env);
int		check_var_suppr(t_com *input, char *env);

/*
**	Lists minishell
*/
t_com	*sh_lstnew(char **tab);
void	sh_lstaddlast(t_com **head, t_com *new);
void	sh_lstdel(t_com **head);

#endif
