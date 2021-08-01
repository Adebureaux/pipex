/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:53:30 by adeburea          #+#    #+#             */
/*   Updated: 2021/07/30 00:11:49 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	quit(t_pip *pip, char *mes)
{
	if (pip)
	{
		ft_free_split(pip->path, NULL);
		if (pip->fd[0] != -1)
			close(pip->fd[0]);
		if (pip->fd[1] != -1)
			close(pip->fd[1]);
	}
	if (!mes)
		exit(EXIT_SUCCESS);
	ft_putstr(2, "\033[0;36mpipex:\e[0m ");
	if (errno)
	{
		perror(mes);
		exit(EXIT_FAILURE);
	}
	ft_putstr(2, mes);
}

void	get_path(t_pip *pip, char **cmd)
{
	int		i;
	char	*temp;
	char	*newpath;

	i = 0;
	while (pip->path[i])
	{
		temp = ft_strjoin(pip->path[i], "/");
		newpath = ft_strjoin(temp, cmd[0]);
		if (access(newpath, X_OK) != -1)
		{
			//execve(newpath, cmd, environ);
			printf("FOUND %s\n", newpath);
			//free(newpath);
			//free(temp);
			//ft_free_split(pip->path, NULL);
			return ;
		}
		free(newpath);
		free(temp);
		i++;
	}
	quit(pip, "command not found\n");
}

void	execute_out(t_pip *pip, char *av)
{
	close(pip->pipe_fd[1]);
	dup2(pip->pipe_fd[0], 0);
	dup2(pip->fd[1], 1);
	close(pip->pipe_fd[0]);
	pip->cmd_out = ft_split(av, ' ');
	// if (execve(pip->cmd_out[0], pip->cmd_out, environ) == -1)
	// 	quit(pip, "invalid command\n");
	get_path(pip, pip->cmd_out);
}

void	pipex(t_pip *pip, char **av, char **ep)
{
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
		{
			pip->path = ft_split(&ep[0][5], ':');
			break ;
		}
		ep++;
	}
	if (!pip->path || !pip->path[0])
		quit(pip, "failed to get $PATH\n");
	pip->fd[0] = open(av[1], O_RDONLY);
	if (pip->fd[0] == -1)
		quit(pip, av[1]);
	pip->fd[1] = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (pip->fd[1] == -1)
		quit(pip, av[4]);
	if (pipe(pip->pipe_fd) == -1)
		quit(pip, "failed to pipe\n");
	pip->pid = fork();
	if (pip->pid < 0)
		quit(pip, "failed to fork\n");
	if (pip->pid == 0)
		execute_out(pip, av[3]);

}

int	main(int ac, char **av, char **ep)
{
	t_pip	pip;

	if (ac != 5)
		quit(NULL, "usage: ./pipex file1 cmd1 cmd2 file2\n");
	pip.path = NULL;
	pip.cmd_in = NULL;
	pip.cmd_out = NULL;
	pipex(&pip, av, ep);
	quit(&pip, NULL);
}
