/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:04:49 by pipolint          #+#    #+#             */
/*   Updated: 2024/02/02 13:16:33 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>

typedef struct s_pipex
{
	char	*path;
	int		infile;
	int		outfile;
	int		pipes[2];
	int		empty_path;
	pid_t	child1;
	pid_t	child2;
}	t_pipex;

// PATH utils
//int	valid_cmd(char *filename, char *path);
char	*get_path(char **envp);
void	error_message(char *str, int perr_flag, int inv_cmd, char **args);
char	*add_suffix(char *path, char *filename);
char	**get_arguments(char *argv);
char	*return_path(char *filename, char *path);
void	init_pipex(t_pipex *pip, char **envp);
char	*no_path(char **argv, int i);

#endif