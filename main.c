/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:53:30 by adeburea          #+#    #+#             */
/*   Updated: 2021/08/28 01:52:55 by adeburea         ###   ########.fr       */
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

void	quit(t_pip *pip, char *mes)
{
	if (!mes)
		exit(EXIT_SUCCESS);
	if (pip)
	{
		close_fd(pip);
	}
	ft_putstr(2, "\033[0;36mpipex:\e[0m ");
	if (errno)
		perror(mes);
	else
		ft_putstr(2, mes);
	exit(EXIT_FAILURE);
}

char	**get_all_paths(char **ep)
{
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
			return (ft_split(&ep[0][5], ':'));
		ep++;
	}
	return (NULL);
}

char	*get_right_path(char **ep, char *cmd)
{
	int		i;
	char	**all_paths;
	char	*temp;
	char	*path;

	i = -1;
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
			all_paths = ft_split(&ep[0][5], ':');
		ep++;
	}
	while (all_paths && all_paths[++i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		path = ft_strjoin(temp, cmd);
		if (access(path, X_OK) != -1)
		{
			free(temp);
			ft_free_split(all_paths, NULL);
			return (path);
		}
		free(path);
		free(temp);
	}
	return (NULL);
}

void	execute_cmd1(t_pip *pip, char **av, char **ep)
{
	pip->cmd1 = ft_split(av[2], ' ');
	pip->path1 = get_right_path(ep, pip->cmd1[0]);
	if (!pip->path1)
		quit(pip, pip->cmd1[0]);
	dup2(pip->pipe[1], STDOUT_FILENO);
	dup2(pip->file[0], STDIN_FILENO);
	close_fd(pip);
	execve(pip->path1, pip->cmd1, ep);
}

void	execute_cmd2(t_pip *pip, char **av, char **ep)
{
	pip->cmd2 = ft_split(av[3], ' ');
	pip->path2 = get_right_path(ep, pip->cmd2[0]);
	if (!pip->path2)
		quit(pip, pip->cmd2[0]);
	dup2(pip->pipe[0], STDIN_FILENO);
	dup2(pip->file[1], STDOUT_FILENO);
	close_fd(pip);
	execve(pip->path2, pip->cmd2, ep);
}

int	main(int ac, char **av, char **ep)
{
	t_pip	pip;

	if (ac != 5)
		quit(NULL, "usage: ./pipex file1 cmd1 cmd2 file2\n");
	pip.file[0] = open(av[1], O_RDONLY);
	if (pip.file[0] == -1)
		quit(&pip, av[1]);
	pip.file[1] = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (pip.file[1] == -1)
		quit(&pip, av[4]);
	if (pipe(pip.pipe) == -1)
		quit(&pip, "failed to pipe\n");
	pip.pid[0] = fork();
	if (pip.pid[0] == 0)
		execute_cmd1(&pip, av, ep);
	pip.pid[1] = fork();
	if (pip.pid[1] == 0)
		execute_cmd2(&pip, av, ep);
	quit(&pip, NULL);
}
