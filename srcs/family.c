/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:56:37 by fepennar          #+#    #+#             */
/*   Updated: 2025/04/29 18:56:48 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_closer(int outfile, int *fd, int prev_fd)
{
	if (prev_fd > 2)
		close(prev_fd);
	if (fd && fd[0] > 2)	
		close(fd[0]);
	if (fd && fd[1] > 2)
		close(fd[1]);
	if (outfile > 2)
		close(outfile);
}

static char	*join_and_check(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	if (access(full, F_OK | X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*result;
	int		i;

	if (!cmd)
		return NULL;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	result = NULL;
	while (paths[i] && result == NULL)
	{
		result = join_and_check(paths[i], cmd);
		i++;
	}
	free_split(paths);
	return (result);
}

void	child_process(t_pipe *data, int prev_fd, int *fd, int idx)
{
	char	**cmd;
	char	*path;

	if (dup2(prev_fd, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
	{
		fd_closer(data->outfile, fd, prev_fd);
		exit_error(data, "dup2", "prev_fd || fd[1]");
	}
	cmd = ft_split(data->av[idx], ' ');
	if (!cmd)
		exit_error(data, "split", data->av[idx]);
	path = find_path(cmd[0], data->envp);
	if (!path)
	{
		fd_closer(data->outfile, fd, prev_fd);
		free_split(cmd);
		exit_error(data, "command not found", NULL);
	}
	fd_closer(data->outfile, fd, prev_fd);
	execve(path, cmd, data->envp);
	perror(cmd[0]);
	free_split(cmd);
	free(path);
	exit(1);
}

void	last_child(t_pipe *data, int prev_fd)
{
	char	**cmd;
	char	*path;

	if (dup2(prev_fd, STDIN_FILENO) == -1)
		exit_error(data, "dup2", "prev_fd");
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		exit_error(data, "dup2", "outfile");
	fd_closer(data->outfile, NULL, prev_fd);
	cmd = ft_split(data->av[data->ac - 2], ' ');
	if (!cmd)
		exit_error(data, "split", data->av[data->ac - 2]);
	path = find_path(cmd[0], data->envp);
	if (!path)
	{
		free_split(cmd);
		exit_error(data, "command not found", NULL);
	}
	execve(path, cmd, data->envp);
	perror(cmd[0]);
	free_split(cmd);
	free(path);
	exit(1);
}
