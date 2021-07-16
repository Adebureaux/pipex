/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:53:30 by adeburea          #+#    #+#             */
/*   Updated: 2021/07/12 15:58:52 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_path(t_pip *pip, char **ep)
{
	int	i;

	i = -1;
	while (ep[++i])
	{
		if (!ft_strcmp(ep[i], "PATH=/"))
		{
			pip->path = ft_strdup(ep[i]);
			break ;
		}
	}

}

int	main(int ac, char **av, char **ep)
{
	t_pip	pip;

	(void)ac;
	(void)av;
	printf("%s\n", ep[12]);
	find_path(&pip, ep);
	return (0);
}
