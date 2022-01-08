/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:58:42 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/08 07:27:40 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n--)
	{
		if (*s1++ != *s2++)
			return (*(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1));
		if (*(s1 - 1) == '\0')
			break ;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*dst;

	dst = (void *)malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (0);
	ft_memcpy(dst, s1, ft_strlen(s1) + 1);
	return (dst);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			i;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	i = 0;
	if (!dest && !source)
		return (NULL);
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	dst = dest;
	return (dst);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(len + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2)
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	return (new_str);
}
