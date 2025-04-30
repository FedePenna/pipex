/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fepennar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:10:05 by fepennar          #+#    #+#             */
/*   Updated: 2025/04/28 12:10:08 by fepennar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# include "../libft/libft.h"

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		ac;
	int		cmd_start;
	int		here_doc;
	char	**av;
	char	**envp;
}	t_pipe;

void		open_infile(t_pipe *data);
void		exit_error(char *msg, char *arg);
void		pipex(t_pipe *data);
void		child_process(t_pipe *data, int prev_fd, int *fd, int idx);
void		init_data(t_pipe *data, int ac, char **av, char **envp);
void		last_child(t_pipe *data, int prev_fd);
void		open_outfile(t_pipe *data);
void		free_split(char **split);
int			main(int ac, char **av, char **envp);
char		*find_path(char *cmd, char **envp);

#endif