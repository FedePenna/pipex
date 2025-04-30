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
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*result;
	int		i;

	if (access(cmd, X_OK) == 0)
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

	if (dup2(prev_fd, STDIN_FILENO) == -1)
		exit_error("dup2", "prev_fd");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit_error("dup2", "fd[1]");
	close(fd[0]);
	close(fd[1]);
	cmd = ft_split(data->av[idx], ' ');
	if (!cmd)
		exit_error("split", data->av[idx]);
	path = find_path(cmd[0], data->envp);
	if (!path)
	{
		free_split(cmd);
		exit_error("command", cmd[0]);
	}
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
		exit_error("dup2", "prev_fd");
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		exit_error("dup2", "outfile");
	cmd = ft_split(data->av[data->ac - 2], ' ');
	if (!cmd)
		exit_error("split", data->av[data->ac - 2]);
	path = find_path(cmd[0], data->envp);
	if (!path)
	{
		free_split(cmd);
		exit_error("command", cmd[0]);
	}
	execve(path, cmd, data->envp);
	perror(cmd[0]);
	free_split(cmd);
	free(path);
	exit(1);
}
