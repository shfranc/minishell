/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 10:07:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/05/09 11:26:16 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

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
}				t_com;

/*
**	Beginning
*/
void			ft_increase_shlvl(char ***env);
void			ft_update_pwd(char ***env);
void			ft_display_prompt(void);

/*
**	Read user input
*/
t_com			*ft_read_userinput(char *line);
char			**ft_split_command(char *s);
int				ft_move_endofcommand(char *s);
int				ft_beginwith_semicolon(char *s);
int				ft_check_semicolon(int check, char ***command);

/*
**	Parse command
*/
t_com			*ft_parse_command(char **command);
void			ft_create_cmd_list(t_com **todo, char **command);
char			**ft_split_intoarg(char *s);
int				ft_check_commandblank(char **command);
int				ft_check_quotes(char **command);

/*
**	Parse command 2
*/
void			ft_is_builtin(t_com *elem);
char			*ft_strsub_withoutquotes(char *s, int len);
int				ft_move_endofarg(char *s);
int				ft_nb_quotes(char *s, int len);

/*
**	Execution check
*/
int				ft_launch_command(t_com *input, char **env);
int				ft_check_existing_path(t_com *input);
void			ft_search_through_path(t_com *input, char **path, char **error);
char			**ft_get_path_variable(char **env);
int				ft_display_cmd_err(t_com *input, char *error);

/*
**	Execution fork
*/
void			ft_execute_command(t_com *todo, char ***env);
int				ft_launch_builtin(t_com *todo, char ***env);
void			ft_fork(t_com *elem, char **env);

/*
**	Bluitin cd
*/
void			ft_builtin_cd(t_com *input, char ***env);
int				ft_fetch_oldpwd(t_com *input, char **env);
void			ft_move_to_home(char ***env);
void			ft_display_cd_err(char *pwd);

/*
**	Bluitin echo
*/
void			ft_builtin_echo(t_com *input);

/*
**	Bluitin env
*/
void			ft_builtin_env(t_com *vinput, char ***env);
char			*ft_get_env_variable(char **env, char *var);
void			ft_change_pwd(char **pwd, char ***env);
void			ft_change_oldpwd(char **old_pwd, char ***env);
/*
**	Bluitin exit
*/
void			ft_builtin_exit(t_com	*input);

/*
**	Bluitin setenv
*/
void			ft_builtin_setenv(t_com *input, char ***env);
int				ft_parsing_setenv(t_com *input, char **temp);
int				ft_modify_variable(char ***env, char *new_var);

/*
**	Bluitin unsetenv
*/
void			ft_builtin_unsetenv(t_com *input, char ***env);
int				ft_count_var_suppr(t_com *input, char ***env);
int				ft_check_var_suppr(t_com *input, char *env);

/*
**	Lists minishell
*/
void			ft_handler_father(int signal);
void			ft_handler_child(int signal);

/*
**	Lists minishell
*/
t_com			*ft_sh_lstnew(char **tab);
void			ft_sh_lstaddlast(t_com **head, t_com *new);
void			ft_sh_lstdel(t_com **head);

#endif
