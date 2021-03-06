/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:52:30 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/09 16:10:28 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	pid_t	child_one;
	pid_t	child_two;
	int		fd[2];
	int		command_one_flag;
	int		command_two_flag;
	char	**inputs;
	char	*join_paths;
	char	*join_command_one;
	char	*join_command_two;
	char	**command_one;
	char	**command_two;
	char	*command_one_path;
	char	*command_two_path;
	char	**paths_one;
	char	**paths_two;
}	t_pipex;

void			child_one_process(t_pipex *pipex, char **envp);
void			child_two_process(t_pipex *pipex, char **envp);
void			deal_child_one(t_pipex *pipex, char **envp);
void			deal_child_two(t_pipex *pipex, char **envp);
void			check_paths(char ***paths, char **envp);
void			check_empty_spaces(t_pipex *pipex);
void			find_command_one(t_pipex *pipex);
void			find_command_two(t_pipex *pipex);
void			execute_command_one(t_pipex *pipex, char **envp);
void			execute_command_two(t_pipex *pipex, char **envp);
void			command_one_checkage(t_pipex *pipex);
void			command_two_checkage(t_pipex *pipex);
void			free_all_one(t_pipex *pipex);
void			free_all_two(t_pipex *pipex);
void			free_ptr(char **ptr);
int				join_one_null(t_pipex *pipex);
int				join_two_null(t_pipex *pipex);

size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(const char *s1);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strjoin(const char *s1, const char *s2);

char			**ft_split(const char *s, char c);

#endif