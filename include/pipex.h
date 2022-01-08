/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:52:30 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/08 07:14:05 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_pipex
{
	char **inputs;
	char **paths;
} t_pipex;

int				deal_child_one (t_pipex *pipex, char **envp, int *fd);
int				deal_child_two (t_pipex *pipex, char **envp, int *fd);
void			check_paths (t_pipex *pipex, char **envp);
int				execute_command_one (t_pipex *pipex);
int				execute_command_two (t_pipex *pipex);

size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s1);
void			*ft_memcpy(void *dst, const void *src, size_t n);

static size_t	get_wordsnum(const char *s, char c);
static size_t	get_wordlen(const char *s, char c);
static char		*worddup(const char *s, size_t len);
static void		*free_all(char **res, size_t stop);
char			**ft_split(const char *s, char c);


# endif