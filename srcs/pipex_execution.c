/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:14:11 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/08 14:00:16 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void check_paths (t_pipex *pipex, char **envp)
{
	char *get_path;
	char **paths;
	int i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=",envp[i], 5) == 0)
			get_path = ft_strdup(envp[i] + 5);
		i++;
	}
	pipex->paths = ft_split(get_path, ':');
}

void find_command_one (t_pipex *pipex)
{
	int i;
	
	
	//check_empty_spaces(pipex);
	pipex->command_one = ft_split(pipex->inputs[2], ' ');
	i= 0;
	while (pipex->paths[i])
	{
		pipex->join_paths = ft_strjoin(pipex->paths[i], "/");
		//printf("%s\n", pipex->join_paths);
		pipex->join_command_one = ft_strjoin(pipex->join_paths, pipex->command_one[0]);
		free(pipex->join_paths);
		if (access(pipex->join_command_one, F_OK) == 0)
		{
			pipex->command_one_path = pipex->join_command_one;
			
			//printf("found it");
		}
		i++;
	}
}

void find_command_two (t_pipex *pipex)
{
	int i;
	char *join_paths;
	
	//check_empty_spaces(pipex);
	pipex->command_two = ft_split(pipex->inputs[3], ' ');
	i = 0;
	while (pipex->paths[i])
	{
		pipex->join_paths = ft_strjoin(pipex->paths[i], "/");
		pipex->join_command_two = ft_strjoin(pipex->join_paths, pipex->command_two[0]);
		free(pipex->join_paths);
		if (access(pipex->join_command_two, F_OK) == 0)
		{
			pipex->command_two_path = pipex->join_command_two;
			//printf("%s\n", pipex->command_two[0]);
			//printf("found it");
		}
		i++;
	}
}

void execute_command_one(t_pipex *pipex,char **envp)
{
	if (execve(pipex->command_one_path, pipex->command_one, envp) == -1)
	{
		perror("Error 6: Command 1 not working");
		exit(1);
	}
}

void execute_command_two(t_pipex *pipex,char **envp)
{
	if (execve(pipex->command_two_path, pipex->command_two, envp) == -1)
	{
		perror("Error 7: Command 2 not working");
		exit(1);
	}
}