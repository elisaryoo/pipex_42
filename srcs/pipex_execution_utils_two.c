/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execution_utils_two.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:19:26 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/09 20:40:35 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	join_one_null(t_pipex *pipex)
{
	if (pipex->join_command_one == NULL)
	{
		free_all_one(pipex);
		free(pipex->join_paths);
		free(pipex->join_command_one);
		return (1);
	}
	return (0);
}

int	join_two_null(t_pipex *pipex)
{
	if (pipex->join_command_two == NULL)
	{
		free_all_two(pipex);
		free(pipex->join_paths);
		free(pipex->join_command_two);
		return (1);
	}
	return (0);
}
