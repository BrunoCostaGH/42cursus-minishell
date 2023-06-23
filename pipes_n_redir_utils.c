/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:12:22 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/23 14:05:43 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_file(t_data *data, char *file, int oflag, int *fd_io)
{
	if (*fd_io)
		close(*fd_io);
	*fd_io = open(file, oflag, S_IRWXU);
	if (*fd_io == -1)
		handle_error(data, file, 0);
}

int	get_fd_out(t_data *data, int s_id)
{
	int	id;

	id = s_id;
	while (data->argv.type[id] || data->argv.type[id + 1])
	{
		if (id != s_id && data->argv.type[id - 1] == PIPE)
			break ;
		if (data->argv.type[id] == REDR_OUTPUT)
		{
			open_file(data, data->argv.args[id + 1][0], O_CREAT | O_RDWR | \
			O_TRUNC, &data->file_io[1]);
			clear_token(data, id + 1);
			continue ;
		}
		else if (data->argv.type[id] == REDR_APPEND)
		{
			open_file(data, data->argv.args[id + 1][0], O_CREAT | O_RDWR | \
			O_APPEND, &data->file_io[1]);
			clear_token(data, id + 1);
			continue ;
		}
		id++;
	}
	return (0);
}

static void	get_fd_in_2(t_data *data, int **pipe_fd, const int *id, int *status)
{
	if (data->argv.type[*id] == REDR_DELIM)
	{
		heredoc(data, pipe_fd, *id);
		dup2(data->file_io[0], STDIN_FILENO);
		*status = 1;
		clear_token(data, *id + 1);
	}
	else if (data->argv.type[*id] == REDR_INPUT)
	{
		if (data->file_io[0])
			close(data->file_io[0]);
		data->file_io[0] = open(data->argv.args[*id + 1][0], O_RDONLY);
		if (data->file_io[0] == -1)
		{
			handle_error(data, data->argv.args[*id + 1][0], 0);
			free_darr((void **)pipe_fd);
			exit_shell(data, 0);
		}
		dup2(data->file_io[0], STDIN_FILENO);
		*status = 1;
		clear_token(data, *id + 1);
	}
}

int	get_fd_in(t_data *data, int **pipe_fd, int s_id)
{
	int	id;
	int	status;
	int	o_input;

	id = s_id;
	status = 0;
	o_input = dup(STDIN_FILENO);
	while (data->argv.type[id] && data->argv.type[id] != PIPE)
	{
		if (data->argv.type[id] == 4 || data->argv.type[id] == 5)
			if (status == 1)
				dup2(o_input, STDIN_FILENO);
		get_fd_in_2(data, pipe_fd, &id, &status);
		if (!status)
			id++;
	}
	regroup_argv(data);
	return (status);
}
