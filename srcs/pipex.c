/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:15:44 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/09 11:14:57 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_one_process(t_pipex *pipex, char **envp)
{
	pipex->child_one = fork();
	if (pipex->child_one < 0)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	if (pipex->child_one == 0)
		deal_child_one(pipex, envp);
}

void	child_two_process(t_pipex *pipex, char **envp)
{
	pipex->child_two = fork();
	if (pipex->child_two < 0)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	if (pipex->child_two == 0)
		deal_child_two(pipex, envp);
}

void	deal_child_one(t_pipex *pipex, char **envp)
{
	int	infile;

	infile = open(pipex->inputs[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		perror("Error: file2 ");
		exit(EXIT_FAILURE);
	}
	dup2(infile, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	check_paths(pipex, envp);
	find_command_one(pipex);
	printf("%s\n", pipex->command_one_path);
	execute_command_one(pipex, envp);
}

void	deal_child_two(t_pipex *pipex, char **envp)
{
	int	outfile;

	outfile = open(pipex->inputs[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
	{
		perror("Error: file1 ");
		exit(EXIT_FAILURE);
	}
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipex->fd[1]);
	check_paths(pipex, envp);
	find_command_two(pipex);
	printf("%s", pipex->command_two_path);
	execute_command_two(pipex, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;

	if (argc != 5)
	{
		write(1, "Error, try: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 50);
		exit(1);
		return (1);
	}
	else
	{
		pipex.inputs = argv;
		if (pipe(pipex.fd) == -1)
		{
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
		child_one_process(&pipex, envp);
		child_two_process(&pipex, envp);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		waitpid(pipex.child_one, NULL, 0);
		waitpid(pipex.child_two, NULL, 0);
	}
	return (0); 
}
