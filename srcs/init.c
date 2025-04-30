/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:46:31 by fepennar          #+#    #+#             */
/*   Updated: 2025/04/28 15:46:32 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_pipe *data, int ac, char **av, char **envp)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
	data->here_doc = 0;
	data->cmd_start = 2;
	data->infile = -1;
	data->outfile = -1;
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		data->here_doc = 1;
		data->cmd_start = 3;
	}
}
