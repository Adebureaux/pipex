/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:53:30 by adeburea          #+#    #+#             */
/*   Updated: 2021/07/19 19:49:46 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	quit(t_pip *pip, char *mes)
{
	if (pip)
	{
		free(pip->path);
		free(pip->file_1);
		free(pip->file_2);
		free(pip->cmd_1);
		free(pip->cmd_2);
		if (pip->fd_1 != -1)
			close(pip->fd_1);
		if (pip->fd_2 != -1)
			close(pip->fd_2);
	}
	ft_putstr("\033[0;36mpipex:\e[0m ");
	if (errno)
	{
		perror(mes);
		exit(EXIT_FAILURE);
	}
	ft_putstr(mes);
	exit(EXIT_SUCCESS);
}

void	get_arg(t_pip *pip, char **av)
{
	pip->file_1 = ft_strdup(av[1]);
	pip->file_2 = ft_strdup(av[3]);
	pip->cmd_1 = ft_strdup(av[2]);
	pip->cmd_2 = ft_strdup(av[4]);
	pip->fd_1 = open(pip->file_1, O_RDONLY);
	if (pip->fd_1 == -1)
		quit(pip, pip->file_1);
	pip->fd_2 = open(pip->file_2, O_CREAT);
	if (pip->fd_2 == -1)
		quit(pip, pip->file_2);
}

void	get_path(t_pip *pip, char **ep)
{
	int	i;

	i = -1;
	while (ep[++i])
	{
		if (!ft_strncmp(ep[i], "PATH=", 5))
		{
			pip->path = ft_strdup(&ep[i][5]);
			return ;
		}
	}
}

int	main(int ac, char **av, char **ep)
{
	t_pip	pip;

	if (ac != 5)
		quit(NULL, "usage: ./pipex file1 cmd1 cmd2 file2\n");
	get_path(&pip, ep);
	get_arg(&pip, av);
	quit(&pip, "exited properly\n");
}
