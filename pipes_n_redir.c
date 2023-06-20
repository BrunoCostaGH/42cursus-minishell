/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:36:35 by tabreia-          #+#    #+#             */
/*   Updated: 2023/06/19 20:53:14 by bsilva-c         ###   ########.fr       */
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

static void	run_token_logic(t_data *data, int **pipe_fd, int id, int pipe_index)
{
	while (id > 0 && pipe_fd[pipe_index])
		pipe_index++;
	data->exit_status = 0;
	(void)get_fd_out(data, id);
	if (get_fd_in(data, pipe_fd, id) == 0)
	{
		if (id > 0 && data->argv.type[id - 1] == PIPE)
		{
			if (data->argv.type[id] == PIPE)
				pipe_index--;
			dup2(pipe_fd[pipe_index - 1][0], STDIN_FILENO);
		}
	}
	if (data->file_io[1])
		dup2(data->file_io[1], STDOUT_FILENO);
	else if (data->argv.type[id] == PIPE)
		dup2(pipe_fd[pipe_index][1], STDOUT_FILENO);
	close_pipes(pipe_fd, pipe_index);
	find_command(data, data->argv.args[id]);
	if (data->file_io[0])
		close(data->file_io[0]);
	if (data->file_io[1])
		close(data->file_io[1]);
	free_darr((void **)pipe_fd);
	exit_shell(data, 0);
}

static void	run_token_logic_chil(t_data *data, int **pipe_fd, int *pid)
{
	int	id;
	int	pipe_index;

	id = 0;
	while (data->argv.args[++id])
	{
		pipe_index = id;
		if (data->argv.type[id - 1] != PIPE)
			continue ;
		while (data->argv.type[pipe_index] && data->argv.type[pipe_index] != 1)
			pipe_index++;
		if (data->argv.type[pipe_index] == PIPE)
		{
			pipe_index = 0;
			while (pipe_fd[pipe_index])
				pipe_index++;
			pipe_fd[pipe_index] = ft_calloc(2 + 1, sizeof(int));
			if (!pipe_fd[pipe_index])
				return ;
			pipe(pipe_fd[pipe_index]);
		}
		*pid = fork();
		if (*pid == 0)
			run_token_logic(data, pipe_fd, id, 0);
	}
}

int	create_token_logic(t_data *data, int **pipe_fd, int *pid)
{
	int	id;

	id = 0;
	pipe_fd[id] = ft_calloc(2 + 1, sizeof(int));
	if (!pipe_fd[id])
		return (1);
	pipe(pipe_fd[id]);
	*pid = fork();
	if (*pid == 0)
		run_token_logic(data, pipe_fd, id, 0);
	else
		run_token_logic_chil(data, pipe_fd, pid);
	return (0);
}

int	check_tokens(t_data *data)
{
	int		pid;
	int		pipe_amount;
	int		**pipe_fd;

	if (!data->argv.args)
		return (0);
	pipe_amount = iarr_len(data->argv.type);
	if (pipe_amount)
	{
		pipe_fd = ft_calloc(pipe_amount + 2, sizeof(int *));
		if (!pipe_fd)
			return (0);
		if (create_token_logic(data, pipe_fd, &pid))
			return (1);
		close_pipes(pipe_fd, iarr_len(data->argv.type));
		while (waitpid(pid, &data->exit_status, WUNTRACED) != -1)
			;
		set_error_status(data, 0);
		while (waitpid(-1, 0, 0) != -1)
			;
		free_darr((void **)pipe_fd);
		return (1);
	}
	return (0);
}
