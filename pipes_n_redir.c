/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:36:35 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/29 19:08:10 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_input_file(t_data *data, int **pipe_fd, int *fd_in, int *id)
{
	if (data->argv.type[*id] == REDR_DELIM)
	{
		here_doc(data, fd_in, *id++);
		dup2(*fd_in, STDIN_FILENO);
	}
	else if (data->argv.type[*id] == REDR_INPUT)
	{
		*fd_in = open(data->argv.args[*id + 1][0], O_RDONLY);
		if (*fd_in == -1)
		{
			handle_error(data, 0, 0);
			shell_exit(data, 0);
		}
		dup2(*fd_in, STDIN_FILENO);
	}
	else if (*id > 1 && data->argv.type[*id - 2] == REDR_DELIM)
		dup2(pipe_fd[*id - 2][0], STDIN_FILENO);
	else
		dup2(pipe_fd[*id - 1][0], STDIN_FILENO);
}

static void	set_output_file(t_data *data, int **pipe_fd, int *fd_out, int *id)
{
	if (data->argv.type[*id] == PIPE)
		dup2(pipe_fd[*id][1], STDOUT_FILENO);
	else if (fd_out)
		dup2(*fd_out, STDOUT_FILENO);
}

int	create_pipes(t_data *data, int **pipe_fd, int *pid)
{
	int		id;
	int		fd_in;
	int		fd_out;

	id = 0;
	fd_in = 0;
	fd_out = 0;
	if (get_fd_out(data, &fd_out) == 1)
		return (1);
	pipe(pipe_fd[id]);
	*pid = fork();
	if (*pid == 0)
	{
		data->exit_status = 0;
		set_input_file(data, pipe_fd, &fd_in, &id);
		set_output_file(data, pipe_fd, &fd_out, &id);
		close_pipes(pipe_fd, id, 1);
		if (id > 0 && data->argv.type[id - 1] == REDR_DELIM)
			find_command(data, data->argv.args[id - 1]);
		else
			find_command(data, data->argv.args[id]);
		if (fd_in)
			close(fd_in);
		shell_exit(data, 0);
	}
	else
	{
		while (data->argv.args[++id])
		{
			if (data->argv.type[id - 1] != PIPE)
				continue ;
			if (data->argv.type[id] == PIPE)
				pipe(pipe_fd[id]);
			*pid = fork();
			if (*pid == 0)
			{
				data->exit_status = 0;
				set_input_file(data, pipe_fd, &fd_in, &id);
				set_output_file(data, pipe_fd, &fd_out, &id);
				close_pipes(pipe_fd, id, 1);
				if (data->argv.type[id - 1] == REDR_DELIM)
					find_command(data, data->argv.args[id - 1]);
				else
					find_command(data, data->argv.args[id]);
				if (fd_in)
					close(fd_in);
				shell_exit(data, 0);
			}
		}
	}
	if (fd_out)
		close(fd_out);
	return (0);
}

int	check_for_pipes(t_data *data)
{
	int		pid;
	int		pipe_amount;

	if (!data->argv.args)
		return (0);
	pipe_amount = len_darr((void **)data->argv.type);
	if (pipe_amount)
	{
		if (create_pipes(data, data->argv.pipe_fd, &pid))
			return (1);
		close_pipes(data->argv.pipe_fd, -1, len_darr((void **)data->argv.type));
		while (waitpid(pid, &data->exit_status, WUNTRACED) != -1)
			;
		set_error_status(data, 0);
		while (waitpid(-1, 0, 0) != -1)
			;
		return (1);
	}
	return (0);
}