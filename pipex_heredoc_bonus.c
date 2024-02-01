/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:59:02 by pipolint          #+#    #+#             */
/*   Updated: 2024/01/29 16:04:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_heredoc(t_pipex *pip, int argc)
{
	if (!(ft_strncmp(pip->args[1], "here_doc", 8)))
	{
		pip->heredoc_flag = 1;
		if (argc < 6)
		{
			ft_putendl_fd("Invalid number of arguments", 2);
			exit(EXIT_FAILURE);
		}
	}
	else
		pip->heredoc_flag = 0;
	pip->cmds = (argc - 3) - pip->heredoc_flag;
}

static void	parent_process_heredoc(int *pipes)
{
	wait(NULL);
	close(pipes[1]);
	if (dup2(pipes[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(pipes[0]);
}

static void	child_process_heredoc(t_pipex *pip, int *pipes, char **line)
{
	close(pipes[0]);
	*line = get_next_line(STDIN_FILENO);
	while (*line)
	{
		if (!ft_strncmp(*line, pip->args[2], ft_strlen(*line) - 1)
			&& ft_strlen(*line) - 1 == ft_strlen(pip->args[2]))
		{
			free(*line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(*line, pipes[1]);
		free(*line);
		*line = get_next_line(STDIN_FILENO);
	}
	if (*line)
		free(*line);
	close(pipes[1]);
}

void	here_doc(t_pipex *pip, int *pipes)
{
	char	*line;
	pid_t	n;

	if (pipe(pipes) < 0)
		error_message(NULL, 1, 1);
	n = fork();
	if (n == 0)
		child_process_heredoc(pip, pipes, &line);
	else
		parent_process_heredoc(pipes);
}
