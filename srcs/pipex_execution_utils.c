/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execution_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 11:25:17 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/09 20:19:00 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	command_one_checkage(t_pipex *pipex)
{
	if (pipex->command_one_flag == 0)
	{
		perror("Error: cmd1 not found");
		free_all_one(pipex);
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
	int	y;
	int	z;

	y = 0;
	z = 0;
	if (pipex->paths_one)
	{
		while (pipex->paths_one[y])
		{
			free(pipex->paths_one[y]);
			y++;
		}
		free(pipex->paths_one);
	}
	while (pipex->command_one[z])
	{
		free(pipex->command_one[z]);
		z++;
	}
	free(pipex->command_one);
}

void	free_all_two(t_pipex *pipex)
{
	int	y;
	int	z;

	y = 0;
	z = 0;
	if (pipex->paths_two)
	{
		while (pipex->paths_two[y])
		{
			free(pipex->paths_two[y]);
			y++;
		}
		free(pipex->paths_two);
	}
	while (pipex->command_two[z])
	{
		free(pipex->command_two[z]);
		z++;
	}
	free(pipex->command_two);
}
