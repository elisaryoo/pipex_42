/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:15:44 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/08 14:45:52 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int deal_child_one (t_pipex *pipex, char **envp)
{
	int infile;
	
	infile = open (pipex->inputs[1], O_RDONLY , 0777);
	if (infile == -1)
	{
		perror("Error 5: infile");
		exit(EXIT_FAILURE);
	}
	dup2(infile, STDIN_FILENO);
	dup2(pipex->fd[1],STDOUT_FILENO);
	close(pipex->fd[0]);
	//close(infile);
	check_paths(pipex, envp);
	find_command_one(pipex);
	printf("%s", pipex->command_one_path);
	execute_command_one(pipex, envp);
	return 0;
}

int deal_child_two (t_pipex *pipex, char **envp)
{
	int outfile;
	
	outfile = open (pipex->inputs[4], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if (outfile == -1)
	{
		perror("Error 4: outfile");
		exit(EXIT_FAILURE);
	}
	dup2(pipex->fd[0],STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipex->fd[1]);
	check_paths(pipex, envp);
	find_command_two(pipex);
	execute_command_two(pipex, envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t		child_one;
	pid_t		child_two;
	t_pipex		pipex;

	if (argc != 5)
	{
		write(1, "Error, please do try: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 60);
		return (1);
	}
	else
	{
		pipex.inputs = argv;
		if (pipe(pipex.fd) == -1)
		{
			perror("Error 1: ");
			exit(EXIT_FAILURE);
		}
		child_one = fork();
		if (child_one < 0)
		{
			perror("Error 2: ");
			exit(EXIT_FAILURE);
		}
		if (child_one == 0)
			deal_child_one(&pipex, envp);
		child_two = fork();
		if (child_two < 0)
		{
			perror("Error 3: ");
			exit(EXIT_FAILURE);
		}
		if (child_two == 0)
			deal_child_two(&pipex, envp);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		waitpid(child_one, NULL, 0);
		waitpid(child_two, NULL, 0);
	}
}