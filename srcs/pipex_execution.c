/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:14:11 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/09 11:18:26 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_paths(t_pipex *pipex, char **envp)
{
	char	*get_path;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			get_path = ft_strdup(envp[i] + 5);
		i++;
	}
	pipex->paths = ft_split(get_path, ':');
	free(get_path);
}

void	find_command_one(t_pipex *pipex)
{
	int	i;
	
	pipex->command_one_flag = 0;
	//pipex->command_one_path = 0;
	pipex->command_one = ft_split(pipex->inputs[2], ' '); //ls -la
	i = 0;
	while (pipex->paths[i])
	{
		pipex->join_paths = ft_strjoin(pipex->paths[i], "/");
		pipex->join_command_one = ft_strjoin(pipex->join_paths, \
											pipex->command_one[0]); // usr/bin/ls
		if (access(pipex->join_command_one, F_OK) == 0)
		{
			pipex->command_one_path = pipex->join_command_one; //command_one_path = usr/bin/ls 
			pipex->command_one_flag = 1;
			//free(pipex->join_command_one);
			break;
		}
		free(pipex->join_paths);
		free(pipex->join_command_one);
		i++;
	}
	if (pipex->command_one_flag == 0)
	{
		perror("Error: cmd1 not found");
		//free(pipex->command_one_path);
		exit(1);
	}
}

void	find_command_two(t_pipex *pipex)
{
	int		i;
	char	*join_paths;
	
	pipex->command_two_flag = 0;
	//pipex->command_two_path = 0;
	pipex->command_two = ft_split(pipex->inputs[3], ' ');
	i = 0;
	while (pipex->paths[i])
	{
		pipex->join_paths = ft_strjoin(pipex->paths[i], "/");
		pipex->join_command_two = ft_strjoin(pipex->join_paths, \
											pipex->command_two[0]);
		if (access(pipex->join_command_two, F_OK) == 0)
		{
			pipex->command_two_path = pipex->join_command_two;
			pipex->command_two_flag = 1;
			//free(pipex->join_command_two);
			break;
		}
		free(pipex->join_paths);
		free(pipex->join_command_two);
		i++;
	}
	if (pipex->command_two_flag == 0)
	{
		perror("Error: cmd2 not found");
		//free(pipex->command_two_path);
		exit(1);
	}
}

void	execute_command_one(t_pipex *pipex, char **envp)
{
	/* if (pipex->command_one_path == NULL)
        pipex->command_one_path = ft_strdup("/bin"); */
	if (execve(pipex->command_one_path, pipex->command_one, envp) == -1)
	{
		perror("Error 3: cmd1 not found");
		free(pipex->command_one_path);
		int i;
		i = 0;
		while (pipex->command_one[i])
		{
			free(pipex->command_one[i]);
			i++;
		}
		exit(1);
	}
}

void	execute_command_two(t_pipex *pipex, char **envp)
{
	/* if (pipex->command_two_path == NULL)
        pipex->command_two_path = ft_strdup("/bin"); */
	if (execve(pipex->command_two_path, pipex->command_two, envp) == -1)
	{
		perror("Error 4: cmd2 not found");
		free(pipex->command_one_path);
		int i;
		i = 0;
		while (pipex->command_two[i])
		{
			free(pipex->command_two[i]);
			i++;
		}
		exit(1);
	}
}
