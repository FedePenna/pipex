/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:41:08 by fepennar          #+#    #+#             */
/*   Updated: 2025/04/29 18:41:10 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipe *data)
{
	int		i;
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	i = data->cmd_start;
	prev_fd = data->infile;
	while (i < data->ac - 2)
	{
		if (pipe(fd) == -1)
			exit_error(data, "pipe", NULL);
		pid = fork();
		if (pid < 0)
			exit_error(data, "fork", NULL);
		if (pid == 0)
			child_process(data, prev_fd, fd, i);
		waitpid(pid, NULL, 0);
		fd_closer(fd[1], NULL, prev_fd);
		prev_fd = fd[0];
		i++;
	}
	last_child(data, prev_fd);
}
