/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:23:01 by fepennar          #+#    #+#             */
/*   Updated: 2025/04/28 15:23:03 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(char *msg, char *arg)
{
	ft_putstr_fd("Error: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	perror(msg);
	exit(1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	data;

	if (ac < 5)
	{
		ft_putstr_fd("The Usage ./pipex f1 cmd1 cmd2 f2..etc", 2);
		return (1);
	}
	init_data(&data, ac, av, envp);
	if (data.here_doc)
	{
		//heredoc :P
	}
	else
		open_infile(&data);
	open_outfile(&data);
	pipex(&data);
	return (0);
}
