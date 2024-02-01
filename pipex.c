/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:37:56 by pipolint          #+#    #+#             */
/*   Updated: 2024/02/01 19:27:11 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(char *str, int perr_flag, int inv_cmd, char **args)
{
	if (perr_flag && !inv_cmd)
	{
		perror(str);
		exit(1);
	}
	else if (inv_cmd)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		ft_free_split(args);
		exit(127);
	}
	else
	{
		ft_putendl_fd(str, 2);
		exit(1);
	}
}

void	ft_dup_and_check(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		exit(EXIT_FAILURE);
}

void	child_1(t_pipex *pip, char **argv, char **envp)
{
	char	**args;
	char	*cmd_path;
	int		exec_status;

	pip->infile = open(argv[1], O_RDONLY);
	if (pip->infile < 0)
		error_message(argv[1], 1, 0, NULL);
	args = get_arguments(argv[2]);
	if (!args)
		error_message("Couldn't get arguments", 0, 0, NULL);
	cmd_path = return_path(args[0], pip->path);
	close(pip->pipes[0]);
	ft_dup_and_check(pip->infile, STDIN_FILENO);
	close(pip->infile);
	ft_dup_and_check(pip->pipes[1], STDOUT_FILENO);
	exec_status = execve(cmd_path, args, envp);
	printf("Execve status: %d\n", exec_status);
	if (exec_status == -1)
	{
		free(cmd_path);
		error_message(args[0], 0, 1, args);
	}
}

void	child_2(t_pipex *pip, char **argv, char **envp, int argc)
{
	char	**args;
	char	*cmd_path;
	int		exec_status;

	pip->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pip->outfile < 0)
		error_message(argv[argc - 1], 1, 0, NULL);
	args = get_arguments(argv[3]);
	if (!args)
		error_message("Couldn't get arguments", 0, 0, NULL);
	cmd_path = return_path(args[0], pip->path);
	if (!args)
		exit(EXIT_FAILURE);
	close(pip->pipes[1]);
	ft_dup_and_check(pip->outfile, STDOUT_FILENO);
	close(pip->outfile);
	ft_dup_and_check(pip->pipes[0], STDIN_FILENO);
	exec_status = execve(cmd_path, args, envp);
	if (exec_status == -1)
	{
		free(cmd_path);
		error_message(NULL, 0, 1, args);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pip;
	int		status;

	if (argc != 5)
	{
		ft_putendl_fd("Invalid number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	init_pipex(&pip, envp, argv);
	pipe(pip.pipes);
	pip.child1 = fork();
	if (pip.child1 == 0)
		child_1(&pip, argv, envp);
	pip.child2 = fork();
	if (pip.child2 == 0)
		child_2(&pip, argv, envp, argc);
	close(pip.pipes[0]);
	close(pip.pipes[1]);
	waitpid(pip.child1, &status, 0);
	waitpid(pip.child2, &status, 0);
	exit(WEXITSTATUS(status));
}
