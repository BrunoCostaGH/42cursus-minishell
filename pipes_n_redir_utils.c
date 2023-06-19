/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:12:22 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/19 20:16:19 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_file(t_data *data, char *file, int oflag, int *fd_io)
{
	if (*fd_io)
		close(*fd_io);
	*fd_io = open(file, oflag, S_IRWXU);
	if (*fd_io == -1)
		handle_error(data, 0, 0);
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

static void	here_doc(t_data *data, int id)
{
	char	*str;

	init_tmp(data);
	open_file(data, data->tmp_file, O_CREAT | O_RDWR | O_TRUNC, \
	&data->file_io[0]);
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

static void	get_fd_in_2(t_data *data, int **pipe_fd, const int *id, int *status)
{
	if (data->argv.type[*id] == REDR_DELIM)
	{
		here_doc(data, *id);
		dup2(data->file_io[0], STDIN_FILENO);
		*status = 1;
	}
	else if (data->argv.type[*id] == REDR_INPUT)
	{
		data->file_io[0] = open(data->argv.args[*id + 1][0], O_RDONLY);
		if (data->file_io[0] == -1)
		{
			handle_error(data, 0, 0);
			free_darr((void **)pipe_fd);
			exit_shell(data, 0);
		}
		dup2(data->file_io[0], STDIN_FILENO);
		*status = 1;
	}
}

int	get_fd_in(t_data *data, int **pipe_fd, int s_id)
{
	int	id;
	int	status;

	status = 0;
	id = s_id;
	while (data->argv.type[id] && data->argv.type[id] != PIPE)
		id++;
	id--;
	while (id >= 0 && data->argv.type[id])
	{
		if ((id == 0 && (data->argv.type[id] == 0 || \
		data->argv.type[id] == PIPE)) || id < s_id)
			break ;
		if (status == 1 && (data->argv.type[id] == REDR_DELIM || \
		data->argv.type[id] == REDR_INPUT))
			clear_token(data, id + 1);
		else
			get_fd_in_2(data, pipe_fd, &id, &status);
		if (!status)
			id--;
	}
	regroup_argv(data);
	return (status);
}
