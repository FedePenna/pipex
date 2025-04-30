/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:12 by fepennar          #+#    #+#             */
/*   Updated: 2025/04/28 16:34:14 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_infile(t_pipe *data)
{
	data->infile = open(data->av[1], O_RDONLY);
	if (data->infile < 0)
		exit_error("infile", data->av[1]);
}

void	open_outfile(t_pipe *data)
{
	if (data->here_doc)
		data->outfile = open(data->av[data->ac - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->outfile = open(data->av[data->ac - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->outfile < 0)
		exit_error("outfile", data->av[data->ac - 1]);
}
