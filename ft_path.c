/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:18:41 by adeburea          #+#    #+#             */
/*   Updated: 2021/08/30 11:24:44 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	all_paths = get_all_paths(ep);
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
	ft_free_split(all_paths, NULL);
	return (NULL);
}
