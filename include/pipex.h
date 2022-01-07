/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:52:30 by eryoo             #+#    #+#             */
/*   Updated: 2022/01/06 21:36:11 by eryoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_pipex
{
    char **inputs;
} t_pipex;

int deal_child_one (t_pipex *pipex, char **envp, int *fd);
int deal_child_two (t_pipex *pipex, char **envp, int *fd);
int execute_command_one (t_pipex *pipex, char **envp);
int execute_command_two (t_pipex *pipex, char **envp);

# endif