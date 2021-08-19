/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:53:30 by adeburea          #+#    #+#             */
/*   Updated: 2021/08/18 10:47:54 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	quit(t_pip *pip, char *mes)
{
	if (pip)
	{
		ft_free_split(pip->test_path, NULL);
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
	else
		ft_putstr(2, mes);
}

void	get_path(t_pip *pip, char **cmd)
{
	int		i;
	char	*temp;
	char	*test;

	i = 0;
	while (pip->test_path[i])
	{
		temp = ft_strjoin(pip->test_path[i], "/");
		test = ft_strjoin(temp, cmd[0]);
		if (access(test, X_OK) != -1)
		{
			free(temp);
			pip->path = test;
			return ;
		}
		free(test);
		free(temp);
		i++;
	}
	quit(pip, "command not found\n");
}

void	execute(t_pip *pip, char *av, char **ep, int in, int out)
{
	close(pip->pipe_fd[in]);
	dup2(pip->pipe_fd[out], out);
	dup2(pip->fd[in], in);
	close(pip->pipe_fd[out]);
	pip->cmd[in] = ft_split(av, ' ');
	//printf("%s\n", pip->cmd[in][0]);
	get_path(pip, pip->cmd[in]);
	//printf("%s\n", pip->path);
	printf("res = %d\n", execve(pip->path, av, ep));
}

void	pipex(t_pip *pip, char **av, char **ep)
{
	while (*ep)
	{
		if (!ft_strncmp(*ep, "PATH=", 5))
		{
			pip->test_path = ft_split(&ep[0][5], ':');
			break ;
		}
		ep++;
	}
	if (!pip->test_path || !pip->test_path[0])
		quit(pip, "failed to get $PATH\n");
	pip->fd[0] = open(av[1], O_RDONLY);
	if (pip->fd[0] == -1)
		quit(pip, av[1]);
	pip->fd[1] = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (pip->fd[1] == -1)
		quit(pip, av[4]);
	if (pipe(pip->pipe_fd) == -1)
		quit(pip, "failed to pipe\n");
	// IN
	get_path(pip, pip->cmd[in]);
	execve("cat", pip->path, ep);
	//execute(pip, ft_split(av[3], ' '), ep, 1, 0);
	// FORK HERE
	// pip->pid = fork();
	// if (pip->pid < 0)
	// 	quit(pip, "failed to fork\n");
	// if (pip->pid == 0)
	// 	execute_out(pip, av[3]);

}

int	main(int ac, char **av, char **ep)
{
	t_pip	pip;

	if (ac != 5)
		quit(NULL, "usage: ./pipex file1 cmd1 cmd2 file2\n");
	pip.test_path = NULL;
	pip.path = NULL;
	pip.cmd[0] = NULL;
	pip.cmd[1] = NULL;
	pipex(&pip, av, ep);
	quit(&pip, NULL);
}
