/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:53:30 by adeburea          #+#    #+#             */
/*   Updated: 2021/08/30 11:28:05 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(t_pip *pip)
{
	close(pip->pipe[0]);
	close(pip->pipe[1]);
	close(pip->file[0]);
	close(pip->file[1]);
}

void	quit(char *mes)
{
	ft_putstr(2, "\033[0;36mpipex:\e[0m ");
	if (errno)
		perror(mes);
	else
		ft_putstr(2, mes);
	exit(EXIT_FAILURE);
}

void	execute_cmd1(t_pip *pip, char **av, char **ep)
{
	pip->cmd[0] = ft_split(av[2], ' ');
	pip->path[0] = get_right_path(ep, pip->cmd[0][0]);
	if (!pip->path[0])
		quit(pip->cmd[0][0]);
	dup2(pip->pipe[1], STDOUT_FILENO);
	dup2(pip->file[0], STDIN_FILENO);
	close_fd(pip);
	execve(pip->path[0], pip->cmd[0], ep);
}

void	execute_cmd2(t_pip *pip, char **av, char **ep)
{
	pip->cmd[1] = ft_split(av[3], ' ');
	pip->path[1] = get_right_path(ep, pip->cmd[1][0]);
	if (!pip->path[1])
		quit(pip->cmd[1][0]);
	dup2(pip->pipe[0], STDIN_FILENO);
	dup2(pip->file[1], STDOUT_FILENO);
	close_fd(pip);
	execve(pip->path[1], pip->cmd[1], ep);
}

int	main(int ac, char **av, char **ep)
{
	t_pip	pip;

	if (ac != 5)
		quit("usage: ./pipex file1 cmd1 cmd2 file2\n");
	pip.file[0] = open(av[1], O_RDONLY);
	if (pip.file[0] == -1)
		quit(av[1]);
	pip.file[1] = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (pip.file[1] == -1)
		quit(av[4]);
	if (pipe(pip.pipe) == -1)
		quit("failed to pipe\n");
	pip.pid[0] = fork();
	if (pip.pid[0] == 0)
		execute_cmd1(&pip, av, ep);
	pip.pid[1] = fork();
	if (pip.pid[1] == 0)
		execute_cmd2(&pip, av, ep);
	close_fd(&pip);
	waitpid(pip.pid[0], NULL, 0);
	waitpid(pip.pid[1], NULL, 0);
	return (0);
}
