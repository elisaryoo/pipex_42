/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:14:11 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/09 20:40:20 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_paths(char ***paths, char **envp)
{
	char	*get_path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			get_path = ft_strdup(envp[i] + 5);
		i++;
	}
	*paths = ft_split(get_path, ':');
	free(get_path);
}

void	find_command_one(t_pipex *pipex)
{
	int	i;

	pipex->command_one_flag = 0;
	pipex->command_one_path = 0;
	pipex->command_one = ft_split(pipex->inputs[2], ' ');
	i = 0;
	while (pipex->paths_one[i])
	{
		pipex->join_paths = ft_strjoin(pipex->paths_one[i], "/");
		pipex->join_command_one = ft_strjoin(pipex->join_paths, \
											pipex->command_one[0]);
		if (join_one_null(pipex))
			return ;
		if (access(pipex->join_command_one, F_OK) == 0)
		{
			pipex->command_one_path = pipex->join_command_one;
			pipex->command_one_flag = 1;
			break ;
		}
		free(pipex->join_paths);
		free(pipex->join_command_one);
		i++;
	}
	command_one_checkage(pipex);
}

void	find_command_two(t_pipex *pipex)
{
	int		i;

	pipex->command_two_flag = 0;
	pipex->command_two_path = 0;
	pipex->command_two = ft_split(pipex->inputs[3], ' ');
	i = 0;
	while (pipex->paths_two[i])
	{
		pipex->join_paths = ft_strjoin(pipex->paths_two[i], "/");
		pipex->join_command_two = ft_strjoin(pipex->join_paths, \
											pipex->command_two[0]);
		if (join_two_null(pipex))
			return ;
		if (access(pipex->join_command_two, F_OK) == 0)
		{
			pipex->command_two_path = pipex->join_command_two;
			pipex->command_two_flag = 1;
			break ;
		}
		free(pipex->join_paths);
		free(pipex->join_command_two);
		i++;
	}
	command_two_checkage(pipex);
}

void	execute_command_one(t_pipex *pipex, char **envp)
{
	if (pipex->command_one_path == NULL)
	{
		write(2, "Error: cmd1 not found\n", 23);
		exit(1);
	}
	if (execve(pipex->command_one_path, pipex->command_one, envp) == -1)
	{
		perror("Error: ");
		free_all_one(pipex);
		exit(1);
	}
}

void	execute_command_two(t_pipex *pipex, char **envp)
{
	if (pipex->command_two_path == NULL)
	{
		write(2, "Error: cmd2 not found\n", 23);
		exit(1);
	}
	if (execve(pipex->command_two_path, pipex->command_two, envp) == -1)
	{
		perror("Error: ");
		free_all_two(pipex);
		exit(1);
	}
}
