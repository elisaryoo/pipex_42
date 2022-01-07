/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 18:15:44 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/07 17:56:37 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int execute_command_one (char **envp)
{
	char **get_path;
	char **paths;
	int i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4))
		i++;
	
	paths = ft_split(envp[i] + 5, ':');
	int x = 0;
	 while (paths[x])
    {
        printf("%s\n", paths[i]);
        x++;
    }
	printf("hello world");
	return (0);
}

int execute_command_two (t_pipex *pipex, char **envp)
{
	
}

int deal_child_one (char **argv, char **envp, int *fd)
{
	int infile;
	
	infile = open (argv[1], O_RDONLY, 0777);
	if (infile == -1)
	{
		perror("Error: infile");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0],STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[1]);
	execute_command_one(envp);
	return 0;
}

int deal_child_two (char **argv, char **envp, int *fd)
{
	int outfile;
	
	outfile = open (argv[4], O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if (outfile == -1)
	{
		perror("Error: outfile");
		exit(EXIT_FAILURE);
	}
	dup2(fd[1],STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	//execute_command_two(pipex, envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t		child_one;
	pid_t		child_two;
	//t_pipex		pipex;
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
			deal_child_one(argv, envp, fd);
		child_two = fork();
		if (child_two < 0)
		{
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
		if (child_two == 0)
			deal_child_two(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
		waitpid(child_one, NULL, 0);
		waitpid(child_two, NULL, 0);
	}
}