/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:03:46 by pipolint          #+#    #+#             */
/*   Updated: 2024/02/01 19:36:57 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_arguments(char *argv)
{
	char	**args;

	args = ft_split(argv, ' ');
	if (!args)
		return (NULL);
	return (args);
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

char	*get_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], "PATH", 4)))
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
	//ft_putendl_fd("PATH not found", 2);
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

void	init_pipex(t_pipex *pip, char **envp, char **argv)
{
	char	**cmds;
	char	*path;
	char	*temp;

	pip->child1 = 0;
	pip->child2 = 0;
	pip->infile = 0;
	pip->outfile = 0;
	pip->cmds = NULL;
	pip->path = get_path(envp);
	if (!pip->path)
	{
		cmds = ft_split(argv[2], '/');
		path = ft_strjoin(cmds[0], "");
		ft_free_split(cmds);
		cmds = ft_split(argv[3], '/');
		temp = path;
		path = ft_strjoin(":", temp);
		pip->path = path;
		free(temp);
		ft_free_split(cmds);
	}
	pip->pipes[0] = 0;
	pip->pipes[1] = 0;
}
