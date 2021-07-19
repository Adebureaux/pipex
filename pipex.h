/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:53:41 by adeburea          #+#    #+#             */
/*   Updated: 2021/07/19 19:09:49 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>

#define RED \033[0;31m
#define GREEN \033[0;32m

typedef struct s_pip
{
	char	*path;
	char	*file_1;
	char	*file_2;
	char	*cmd_1;
	char	*cmd_2;
	int		fd_1;
	int		fd_2;
}			t_pip;

size_t	ft_strlen(const char *s);
void	ft_putstr(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);

#endif
