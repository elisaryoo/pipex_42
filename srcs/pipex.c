/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:15:44 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/08 07:14:00 by eryoo            ###   ########.fr       */
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

int execute_command_one (t_pipex *pipex)
{
	int i;
	char 
	
	i= 0;
	while (pipex->paths[i])
	{
		
		i++;
	}
}

/*int execute_command_two (t_pipex *pipex, char **envp)
{
	
}*/

int deal_child_one (t_pipex *pipex, char **envp, int *fd)
{
	int infile;
	
	infile = open (pipex->inputs[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		perror("Error: infile");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0],STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[1]);
	check_paths(pipex, envp);
	execute_command_one(pipex);
	return 0;
}

int deal_child_two (t_pipex *pipex, char **envp, int *fd)
{
	int outfile;
	
	outfile = open (pipex->inputs[4], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if (outfile == -1)
	{
		perror("Error: outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd[1],STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	check_paths(pipex, envp);
	//execute_command_two(pipex, envp);
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
		pipex.inputs = argv;
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