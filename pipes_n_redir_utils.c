/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:12:22 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/16 17:55:57 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_token(t_data *data, int id)
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
	if ((--i >= 0 && data->argv.args[i] && !data->argv.args[i][0]) || \
		(++i >= 0 && data->argv.args[i] && !data->argv.args[i][0]))
	{
		free_darr((void **)data->argv.args[i]);
		while (data->argv.args[++i])
			data->argv.args[i - 1] = data->argv.args[i];
		data->argv.args[i - 1] = 0;
		i = id - 1;
		while (data->argv.type[++i])
			data->argv.type[i - 1] = data->argv.type[i];
		data->argv.type[i - 1] = 0;
	}
}

static void	open_file(t_data *data, char *file, int oflag, int *fd_io)
{
	if (*fd_io)
		close(*fd_io);
	*fd_io = open(file, oflag, S_IRWXU);
	if (*fd_io == -1)
		handle_error(data, 0, 0);
}

int	get_fd_out(t_data *data, int *fd_out)
{
	int	id;

	id = 0;
	while (data->argv.type[id] || data->argv.type[id + 1])
	{
		if (data->argv.type[id] == REDR_OUTPUT)
		{
			open_file(data, data->argv.args[id + 1][0], O_CREAT | O_RDWR | \
			O_TRUNC, fd_out);
			clear_token(data, id + 1);
			continue ;
		}
		else if (data->argv.type[id] == REDR_APPEND)
		{
			open_file(data, data->argv.args[id + 1][0], O_CREAT | O_RDWR | \
			O_APPEND, fd_out);
			clear_token(data, id + 1);
			continue ;
		}
		id++;
	}
	return (0);
}

static void	here_doc(t_data *data, int id)
{
	char	*str;

	init_tmp(data);
	data->file_io[0] = open(data->tmp_file, O_CREAT | O_RDWR | O_TRUNC, \
	S_IRWXU);
	if (data->file_io[0] == -1)
		handle_error(data, 0, 0);
	while (1)
	{
		str = readline("heredoc> ");
		if (*data->argv.args[id + 1] && !ft_strncmp(data->argv.args[id + 1][0], \
		str, ft_strlen(data->argv.args[id + 1][0]) + 1))
			break ;
		write(data->file_io[0], str, ft_strlen(str));
		write(data->file_io[0], "\n", 1);
		if (!*data->argv.args[id + 1])
			break ;
	}
	close(data->file_io[0]);
	data->file_io[0] = open(data->tmp_file, O_RDONLY);
	if (data->file_io[0] == -1)
		handle_error(data, 0, 0);
}

int	get_fd_in(t_data *data, int **pipe_fd)
{
	int	id;
	int	status;

	status = 0;
	id = iarr_len(data->argv.type) - 1;
	while (id >= 0 && data->argv.type[id])
	{
		if (id == 0 && (data->argv.type[id] == REGULAR || \
		data->argv.type[id] == PIPE))
			break ;
		if (status == 1 && (data->argv.type[id] == REDR_DELIM || \
		data->argv.type[id] == REDR_INPUT))
			clear_token(data, id + 1);
		else if (data->argv.type[id] == REDR_DELIM)
		{
			here_doc(data, id);
			dup2(data->file_io[0], STDIN_FILENO);
			status = 1;
		}
		else if (data->argv.type[id] == REDR_INPUT)
		{
			data->file_io[0] = open(data->argv.args[id + 1][0], O_RDONLY);
			if (data->file_io[0] == -1)
			{
				handle_error(data, 0, 0);
				free_darr((void **)pipe_fd);
				exit_shell(data, 0);
			}
			dup2(data->file_io[0], STDIN_FILENO);
			status = 1;
		}
		if (!status)
			id--;
	}
	regroup_argv(data);
	return (status);
}
