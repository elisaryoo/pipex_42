/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:26:17 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/09 16:27:53 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static size_t	get_wordsnum(const char *s, char c)
{
	int		is_word;
	size_t	words;

	words = 0;
	is_word = 0;
	while (*s)
	{
		if (!is_word && *s != c)
		{
			is_word = 1;
			words++;
		}
		else if (is_word && *s == c)
			is_word = 0;
		s++;
	}
	return (words);
}

static size_t	get_wordlen(const char *s, char c)
{
	size_t	length;

	length = 0;
	while (s[length] && s[length] != c)
		length++;
	return (length);
}

static char	*worddup(const char *s, size_t len)
{
	char	*str;
	size_t	offset;

	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	offset = 0;
	while (offset < len)
	{
		str[offset] = s[offset];
		offset++;
	}
	str[offset] = '\0';
	return (str);
}

static void	*free_all(char **res, size_t stop)
{
	size_t	counter;

	counter = 0;
	while (counter < stop)
		free(res[counter]);
	free(res);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	len;
	size_t	words;
	size_t	counter;

	if (s == NULL)
		return (NULL);
	words = get_wordsnum(s, c);
	res = malloc((words + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	counter = 0;
	while (counter < words)
	{
		len = get_wordlen(s, c);
		if (len)
		{
			res[counter] = worddup(s, len);
			if (res[counter++] == NULL)
				return (free_all(res, counter - 1));
		}
		s += len + 1;
	}
	res[counter] = NULL;
	return (res);
}
