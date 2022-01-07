/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:58:42 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/07 17:22:10 by eryoo            ###   ########.fr       */
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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b_size;
	size_t	l_size;
	size_t	s_size;

	b_size = ft_strlen(big);
	l_size = ft_strlen(little);
	if (l_size == 0)
		return ((char *)big);
	else if (l_size > b_size)
		return (NULL);
	if (b_size > len)
		s_size = len;
	else
		s_size = b_size;
	while (l_size <= s_size)
	{
		if (!ft_strncmp(big, little, l_size))
			return ((char *)big);
		big++;
		s_size--;
	}
	return (NULL);
}



