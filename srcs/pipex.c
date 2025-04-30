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
			exit_error("pipe", NULL);
		pid = fork();
		if (pid < 0)
			exit_error("fork", NULL);
		if (pid == 0)
			child_process(data, prev_fd, fd, i);
		close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
		i++;
	}
	last_child(data, prev_fd);
}
