/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:23:37 by pipolint          #+#    #+#             */
/*   Updated: 2024/01/21 15:45:33 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_pipex
{
	pid_t	*pids;
	int		infile;
	int		outfile;
	int		cmds;
	int		heredoc_flag;
	char	**args;
	char	**cmd;
	char	*cmd_path;
	char	*path;
	int		status;
}	t_pipex;

char	*get_path(char **envp, char **argv, int argc);
char	*add_suffix(char *path, char *filename);
char	**get_arguments(char *argv);
char	*return_path(char *filename, char *path);
void	init_pipex(t_pipex *pip, char **argv, char **envp, int argc);
int		open_file(char *filename, int f_type);

void	check_heredoc(t_pipex *pip, int argc);
void	here_doc(t_pipex *pip, int *pipes);

void	exec_cmd(t_pipex *pip);
void	error_message(char *str, int exit_needed, int perror_needed);

void	parent_process(int *pipes);
void	first_process(t_pipex *pip, int *pipes);
void	last_process(t_pipex *pip, int *pipes, int argc);

#endif
