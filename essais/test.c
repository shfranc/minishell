/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:53:20 by sfranc            #+#    #+#             */
/*   Updated: 2017/04/14 11:30:05 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	pid_t	father;
	int		i;
	int		ret;

	i = 0;
	printf("father ID : %d,\t %d\n", getpid(), i++);
	father = fork();
	printf("father ID : %d,\t %d\n", getpid(), i++);
	if (father > 0) // je suis dans le pere
	{
		printf("if > 0, father ID : %d,\t %d\n", getpid(), i++);
		wait(0); // wait prend un pointeur sur int*, em mettant rien en fait c'est 0 donc NULL.
		printf("PAPA\n");	
	}
	if (father == 0) // c'est le fils
	{
		printf("if == 0, father ID : %d,\t %d\n", getpid(), i++);
		ret = execve("/bin/ls", av, NULL);
		printf("%d\n", ret);
	}
	return (0);
}
