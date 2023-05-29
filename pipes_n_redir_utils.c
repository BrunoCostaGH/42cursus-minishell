/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:12:22 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/29 18:49:22 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_argv(t_data *data, int id)
{
	int	i;
	int	k;

	i = id;
	k = 0;
	data->argv.type[i - 1] = 0;
	free(data->argv.args[i][k]);
	data->argv.args[i][k] = 0;
	while (data->argv.args[i][++k])
		data->argv.args[i][k - 1] = data->argv.args[i][k];
	data->argv.args[i][k - 1] = 0;
	while ((i >= 0 && data->argv.args[i] && !data->argv.args[i][0]) || \
	(--i >= 0 && data->argv.args[i] && !data->argv.args[i][0]))
	{
		if (data->argv.args[i])
			free(data->argv.args[i]);
		data->argv.args[i] = 0;
		while (data->argv.args[++i])
			data->argv.args[i - 1] = data->argv.args[i];
		data->argv.args[i - 1] = 0;
		i = id - 1;
		while (data->argv.type[++i])
			data->argv.type[i - 1] = data->argv.type[i];
		data->argv.type[--i] = 0;
	}
}

static void	open_file(t_data *data, char *file, int oflag, int *fd)
{
	if (*fd)
		close(*fd);
	*fd = open(file, oflag, S_IRWXU);
	if (*fd == -1)
		handle_error(data, 0, 0);
}

int	get_fd_out(t_data *data, int *fd)
{
	int	id;

	id = 0;
	while (data->argv.type[id])
	{
		if (data->argv.type[id] == REDR_OUTPUT)
		{
			open_file(data, data->argv.args[id + 1][0], O_CREAT | O_RDWR | \
			O_TRUNC, fd);
			clear_argv(data, id + 1);
			continue ;
		}
		else if (data->argv.type[id] == REDR_APPEND)
		{
			open_file(data, data->argv.args[id + 1][0], O_CREAT | O_RDWR | \
			O_APPEND, fd);
			clear_argv(data, id + 1);
			continue ;
		}
		id++;
	}
	return (0);
}

void	close_pipes(int **pipe_fd, int id, int len)
{
	if (id == -1)
	{
		while (++id != len)
		{
			if (pipe_fd[id])
			{
				close(pipe_fd[id][0]);
				close(pipe_fd[id][1]);
			}
		}
	}
	else
	{
		(void)len;
		while (id >= 0)
		{
			if (pipe_fd[id])
			{
				close(pipe_fd[id][0]);
				close(pipe_fd[id][1]);
			}
			id--;
		}
	}
}

void	here_doc(t_data *data, int *fd, int id)
{
	char	*str;

	init_tmp(data);
	*fd = open(data->tmp_file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (*fd == -1)
		handle_error(data, 0, 0);
	while (1)
	{
		str = readline("heredoc> ");
		if (*data->argv.args[id + 1] && !ft_strncmp(data->argv.args[id + 1][0], \
		str, ft_strlen(data->argv.args[id + 1][0])))
			break ;
		write(*fd, str, ft_strlen(str));
		write(*fd, "\n", 1);
		if (!*data->argv.args[id + 1])
			break ;
	}
	close(*fd);
	*fd = open(data->tmp_file, O_RDONLY);
	if (*fd == -1)
		handle_error(data, 0, 0);
}
