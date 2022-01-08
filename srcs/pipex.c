/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:15:44 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/08 12:11:49 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void execute_command_one(t_pipex *pipex,char **envp)
{
	if (execve(pipex->command_one[0], pipex->command_one, envp) == -1)
	{
		perror("Error 6: Command 1 not working");
		exit(1);
	}
}

void execute_command_two(t_pipex *pipex,char **envp)
{
	if (execve(pipex->command_two[0], pipex->command_two, envp) == -1)
	{
		perror("Error 7: Command 2 not working");
		exit(1);
	}
}

void check_empty_spaces(t_pipex *pipex)
{
	int i;

	i = 0;
	while (pipex->inputs[2] + i != "\0")
	{
		if (pipex->inputs[2] + i == " ")
		{
			printf("is this working");
			perror("Error: Too many blank spaces");
			exit(1);
		}
		printf("is this working");
		i++;
	}
}

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
	char *join_paths;
	
	//check_empty_spaces(pipex);
	pipex->command_one = ft_split(pipex->inputs[2], ' ');
	i= 0;
	while (pipex->paths[i])
	{
		join_paths = ft_strjoin(pipex->paths[i], "/");
		pipex->join_command_one = ft_strjoin(join_paths, pipex->command_one[0]);
		free(join_paths);
		if (access(pipex->join_command_one, F_OK) == 0)
		{
			pipex->command_one[0] = pipex->join_command_one;
			printf("%s\n", pipex->command_one[0]);
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
		join_paths = ft_strjoin(pipex->paths[i], "/");
		pipex->join_command_two = ft_strjoin(join_paths, pipex->command_two[0]);
		free(join_paths);
		if (access(pipex->join_command_two, F_OK) == 0)
		{
			pipex->command_two[0] = pipex->join_command_two;
			printf("%s\n", pipex->command_two[0]);
			//printf("found it");
		}
		i++;
	}
}

int deal_child_one (t_pipex *pipex, char **envp, int *fd)
{
	int infile;
	
	infile = open (pipex->inputs[1], O_RDONLY , 0777);
	if (infile == -1)
	{
		perror("Error 5: infile");
		exit(EXIT_FAILURE);
	}
	dup2(fd[1],STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	//close(infile);
	check_paths(pipex, envp);
	find_command_one(pipex);
	execute_command_one(pipex, envp);
	return 0;
}

int deal_child_two (t_pipex *pipex, char **envp, int *fd)
{
	int outfile;
	
	outfile = open (pipex->inputs[4], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if (outfile == -1)
	{
		perror("Error 4: outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0],STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	//close(outfile);
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
			deal_child_two(&pipex, envp;
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		waitpid(child_one, NULL, 0);
		waitpid(child_two, NULL, 0);
	}
}