/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execution_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:25:17 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/09 12:40:26 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	command_one_checkage(t_pipex *pipex)
{
	if (pipex->command_one_flag == 0)
	{
		perror("Error: cmd1 not found");
		//free_all_one(pipex);
		exit(1);
	}
}

void	command_two_checkage(t_pipex *pipex)
{
	if (pipex->command_two_flag == 0)
	{
		perror("Error: cmd2 not found");
		free_all_two(pipex);
		exit(1);
	}
}

void	free_all_one(t_pipex *pipex)
{
	int y;
	int z;
	
	y = 0;
	z = 0;
	while(pipex->paths[y])
	{
		pipex->paths[y];
		y++;
	}
	//free(pipex->paths);
	while(pipex->command_one[z])
	{
		pipex->command_one[z];
		z++;
	}
	//free(pipex->command_one);
}

void	free_all_two(t_pipex *pipex)
{
	int y;
	int z;
	
	y = 0;
	z = 0;
	while(pipex->paths[y])
	{
		pipex->paths[y];
		y++;
	}
	while(pipex->command_two[z])
	{
		pipex->command_two[z];
		z++;
	}
}

void    free_ptr(char **ptr)
{
	int    i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}