/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:32:20 by pipolint          #+#    #+#             */
/*   Updated: 2024/02/24 20:27:08 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_cmd(t_pipex *pip)
{
	if (execve(pip->cmd_path, pip->cmd, NULL) == -1)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(pip->cmd[0], 2);
		ft_free_split(pip->cmd);
		free(pip->cmd_path);
		free(pip->pids);
		exit(127);
	}
}

void	error_message(char *str, int exit_needed, int perror_needed)
{
	if (exit_needed && perror_needed)
	{
		perror(str);
		exit(1);
	}
	else if (exit_needed)
	{
		ft_putendl_fd(str, 2);
		exit(EXIT_FAILURE);
	}
	else
		ft_putendl_fd(str, 2);
}

void	first_process(t_pipex *pip, int *pipes)
{
	pip->infile = open_file(pip->args[1], 0);
	if (pip->infile < 0)
		error_message(pip->args[1], 1, 1);
	dup2(pip->infile, STDIN_FILENO);
	close(pip->infile);
	close(pipes[0]);
	dup2(pipes[1], STDOUT_FILENO);
	close(pipes[1]);
}

void	last_process(t_pipex *pip, int *pipes, int argc)
{
	if (!pip->heredoc_flag)
		pip->outfile = open_file(pip->args[argc - 1], 1);
	else
		pip->outfile = open_file(pip->args[argc - 1], 3);
	if (pip->outfile < 0)
		error_message(pip->args[argc - 1], 1, 1);
	close(pipes[0]);
	close(pipes[1]);
	dup2(pip->outfile, STDOUT_FILENO);
	close(pip->outfile);
}

void	parent_process(int *pipes)
{
	close(pipes[1]);
	dup2(pipes[0], STDIN_FILENO);
	close(pipes[0]);
}
