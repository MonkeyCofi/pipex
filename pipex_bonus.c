/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:23:27 by pipolint          #+#    #+#             */
/*   Updated: 2024/01/21 15:58:30 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex(t_pipex *pip, int *pipes, int index, int argc)
{
	pip->pids[index] = fork();
	if (pip->pids[index] == 0)
	{
		if (!pip->heredoc_flag)
			pip->cmd = ft_split(pip->args[index + 2], ' ');
		else
			pip->cmd = ft_split(pip->args[index + 3], ' ');
		pip->cmd_path = return_path(pip->cmd[0], pip->path);
		if (index == 0 && !pip->heredoc_flag)
			first_process(pip, pipes);
		else if (index == pip->cmds - 1)
			last_process(pip, pipes, argc);
		else
		{
			close(pipes[0]);
			dup2(pipes[1], STDOUT_FILENO);
			close(pipes[1]);
		}
		exec_cmd(pip);
	}
	else
		parent_process(pipes);
}

void	pipex_loop(t_pipex *pip, int index, int *pipes, int argc)
{
	while (++index < pip->cmds)
	{
		pipe(pipes);
		pipex(pip, pipes, index, argc);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pip;
	int		index;
	int		pipes[2];

	if (argc < 5)
		error_message("Invalid number of arguments", 1, 0);
	index = -1;
	init_pipex(&pip, argv, envp, argc);
	check_heredoc(&pip, argc);
	pip.pids = malloc(sizeof(int) * (pip.cmds));
	if (!pip.pids)
		error_message("Couldn't allocate memory for PIDs", 1, 0);
	if (pip.heredoc_flag)
	{
		ft_putstr_fd("> ", 1);
		here_doc(&pip, pipes);
		pipex_loop(&pip, index, pipes, argc);
	}
	else
		pipex_loop(&pip, index, pipes, argc);
	while (++index < pip.cmds)
		waitpid(pip.pids[index], &pip.status, 0);
	free(pip.pids);
	if (WIFEXITED(pip.status))
		exit(WEXITSTATUS(pip.status));
}
