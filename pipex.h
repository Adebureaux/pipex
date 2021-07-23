/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:53:41 by adeburea          #+#    #+#             */
/*   Updated: 2021/07/22 16:06:20 by adeburea         ###   ########.fr       */
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

#define STDIN 1
#define STDERR 2

typedef struct s_pip
{
	char	**path;
	char	**cmd_in;
	char	**cmd_out;
	int		fd[2];
	int		pipe_fd[2];
	pid_t	pid;
}			t_pip;

size_t	ft_strlen(const char *s);
void	ft_putstr(int fd, char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);

void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);

char	**ft_free_split(char **dst, int *char_nbr);
char	**ft_split(const char *s, char c);

#endif
