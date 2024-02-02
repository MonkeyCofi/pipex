/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:48:34 by pipolint          #+#    #+#             */
/*   Updated: 2024/02/02 16:01:45 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char **envp, char **argv, int argc)
{
	int		i;
	char	**cmds;
	char	*path;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], "PATH", 4)))
			return (&envp[i][5]);
		i++;
	}
	//if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	//	i = 2;
	//else
	//	i = 1;
	//while (++i && i < argc - 1)
	//{
	//	cmds = ft_split(argv[i], '/');
	//	path = ft_strjoin("/", cmds[0]);
	//	ft_free_split(cmds);
	//	temp = path;
	//	path = ft_strjoin(temp, ":");
	//	free(temp);
	//}
	return (path);
}

char	*add_suffix(char *path, char *filename)
{
	char	*new_filename;
	char	*temp;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	new_filename = ft_strjoin(temp, filename);
	if (!new_filename)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (new_filename);
}

char	*return_path(char *filename, char *path)
{
	char	**paths;
	char	*new_filename;
	int		i;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		new_filename = add_suffix(paths[i], filename);
		if (!(access(new_filename, X_OK | F_OK)))
		{
			ft_free_split(paths);
			return (new_filename);
		}
		free(new_filename);
	}
	ft_free_split(paths);
	return (ft_strdup(filename));
}

void	init_pipex(t_pipex *pip, char **argv, char **envp, int argc)
{
	pip->args = argv;
	pip->path = get_path(envp, argv, argc);
	pip->cmd_path = NULL;
	pip->heredoc_flag = 0;
	pip->infile = 0;
	pip->outfile = 0;
	pip->cmds = (argc - 3);
	pip->status = 0;
}

/*
** f_type 0: infile
** f_type 1: outfile
** f_type 2: heredoc infile
** f_type 3: heredoc outfile
*/
int	open_file(char *filename, int f_type)
{
	int	flags;
	int	fd;

	if (f_type == 1 || f_type == 2)
	{
		f_type = 0644;
		flags = O_CREAT | O_WRONLY | O_TRUNC;
		fd = open(filename, flags, f_type);
	}
	else if (f_type == 3)
	{
		f_type = 0644;
		flags = O_CREAT | O_WRONLY | O_APPEND;
		fd = open(filename, flags, f_type);
	}
	else
	{
		flags = O_RDONLY;
		fd = open(filename, flags);
	}
	return (fd);
}
