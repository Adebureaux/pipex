/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 19:29:46 by adeburea          #+#    #+#             */
/*   Updated: 2021/08/30 11:29:41 by adeburea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	int				n;
	void			*ret;
	unsigned char	*ptr;

	n = count * size;
	ret = malloc(n);
	ptr = (unsigned char *)ret;
	if (!ret)
		return (NULL);
	while (n--)
		*ptr++ = 0;
	return (ret);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	if (!ptr_dst && !ptr_src)
		return (NULL);
	while (n--)
		*ptr_dst++ = *ptr_src++;
	return (dst);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	i;
	size_t	j;

	dst_len = ft_strlen(dst);
	i = dst_len;
	j = 0;
	if (dstsize > dst_len)
	{
		while (j < dstsize - dst_len - 1 && src[j])
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
		return (ft_strlen(src) + dst_len);
	}
	else
		return (ft_strlen(src) + dstsize);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	while (start-- && *s)
		s++;
	dst = (char *)malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s, len + 1);
	return (dst);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*dst;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = (char *)malloc(sizeof(char) * len);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, len);
	return (dst);
}
