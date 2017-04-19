/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 10:07:47 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/19 18:54:06 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <signal.h>

# define ERROR "Error"

typedef struct	s_command
{
	char				*path;
	char				**command;
	int					error;
	char				*status;
	struct s_command	*next;
}				t_com;

/*
** Listes minishell
*/
t_com	*sh_lstnew(char **tab);
void	sh_lstaddlast(t_com **head, t_com *new);
void	sh_lstdel(t_com **head);

/*
** Built-in exit
*/
void	builtin_exit(int status);

/*
** read user input
*/
char 	**read_userinput(char **line);

#endif