/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:15:44 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/06 21:36:32 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int execute_command_one (t_pipex *pipex, char **envp)
{
	
}

int execute_command_one (t_pipex *pipex, char **envp)
{
	
}

int deal_child_one (t_pipex *pipex, char **envp, int *fd)
{
	int infile;
	
	infile = open (pipex->inputs[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	dup2(pipex->inputs[1],STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute_command_one(pipex, envp);
}

int deal_child_two (t_pipex *pipex, char **envp, int *fd)
{
	int outfile;
	
	outfile = open (pipex->inputs[4], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if (outfile == -1)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	dup2(pipex->inputs[4],STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute_command_two(pipex, envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t		child_one;
	pid_t		child_two;
	t_pipex		pipex;
	int			fd[2];

	if (argc != 5)
	{
		write(1, "Error, please do try: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 60);
		return (1);
	}
	else
	{
		if (pipe(fd) == -1)
		{
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
		child_one = fork();
		if (child_one < 0)
		{
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
		if (child_one == 0)
			deal_child_one(&pipex, envp, fd);
		child_two = fork();
		if (child_two < 0)
		{
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
		if (child_two == 0)
			deal_child_two(&pipex, envp, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(child_one, NULL, 0);
		waitpid(child_two, NULL, 0);
	}
}