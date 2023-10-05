/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:36:35 by tabreia-          #+#    #+#             */
/*   Updated: 2023/10/05 19:24:47 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(int **pipe_fd, int id)
{
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

static void	run_command(t_data *data, int *pid, int pipe_index, int id)
{
	*pid = fork();
	if (*pid == 0)
	{
		data->exit_status = 0;
		if (data->file_io[1])
			dup2(data->file_io[1], 1);
		else if (data->argv.type[id] == PIPE)
			dup2(data->pipe_fd[pipe_index][1], 1);
		close_pipes(data->pipe_fd, pipe_index);
		find_command(data, data->argv.args[id]);
		reset_io(data);
		exit_shell(data, 0);
	}
}

static int	run_token_logic(t_data *data, int *pid, int id)
{
	int	pipe_index;
	int	status;

	pipe_index = 0;
	while (id > 0 && data->pipe_fd[pipe_index])
		pipe_index++;
	(void)get_fd_out(data, id);
	status = get_fd_in(data, id);
	if (status == 0)
	{
		if (id > 0 && data->argv.type[id - 1] == PIPE)
		{
			if (data->argv.type[id] == PIPE)
				pipe_index--;
			dup2(data->pipe_fd[pipe_index - 1][0], 0);
		}
	}
	else if (status == 2)
		return (1);
	run_command(data, pid, pipe_index, id);
	return (0);
}

int	create_token_logic(t_data *data, int *pid)
{
	int	id;
	int	pipe_index;

	id = 0;
	while (data->argv.args[id] || data->argv.type[id])
	{
		pipe_index = id;
		if (id > 0 && data->argv.type[id - 1] != PIPE)
		{
			id++;
			continue ;
		}
		while (data->argv.type[pipe_index] && data->argv.type[pipe_index] != 1)
			pipe_index++;
		if (data->argv.type[pipe_index] == PIPE)
			if (init_pipe_child(data))
				return (1);
		if (run_token_logic(data, pid, id) == 1)
			return (1);
		reset_io(data);
		id++;
	}
	return (0);
}

int	check_tokens(t_data *data)
{
	int		pid;
	int		pipe_amount;

	if (!data->argv.args)
		return (0);
	pipe_amount = iarr_len(data->argv.type);
	if (pipe_amount)
	{
		if (create_token_logic(data, &pid) == 0)
		{
			close_pipes(data->pipe_fd, iarr_len(data->argv.type));
			while (waitpid(pid, &data->exit_status, 1) == 0)
				;
			set_error_status(data, 0);
			while (waitpid(-1, 0, 0) != -1)
				;
		}
		reset_io(data);
		return (1);
	}
	return (0);
}
