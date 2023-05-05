/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:36:35 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/05 15:26:25 by bsilva-c         ###   ########.fr       */
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

void	create_pipes(t_data *data, int **pipe_fd)
{
	int		id;
	pid_t	pid;

	id = 0;
	pipe_fd[id] = malloc(sizeof(int) * 2);
	pipe(pipe_fd[id]);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_fd[id][1], STDOUT_FILENO);
		close_pipes(pipe_fd, id);
		find_command(data, data->argv.args[id]);
		exit(0);
	}
	else
	{
		while (data->argv.args[++id])
		{
			if (data->argv.args[id + 1])
			{
				pipe_fd[id] = malloc(sizeof(int) * 2);
				pipe(pipe_fd[id]);
			}
			pid = fork();
			if (pid == 0)
			{
				if (pipe_fd[id])
					dup2(pipe_fd[id][1], STDOUT_FILENO);
				dup2(pipe_fd[id - 1][0], STDIN_FILENO);
				close_pipes(pipe_fd, id);
				find_command(data, data->argv.args[id]);
				exit(0);
			}
		}
	}
}

int	check_for_pipes(t_data *data)
{
	int		**pipe_fd;
	int		pipe_amount;

	if (!data->prompt)
		return (0);
	pipe_amount = 0;
	while (data->argv.args[pipe_amount + 1])
		pipe_amount++;
	if (pipe_amount++)
	{
		pipe_fd = ft_calloc(pipe_amount + 1, sizeof(int *));
		create_pipes(data, pipe_fd);
		close_pipes(pipe_fd, pipe_amount);
		while (waitpid(-1, NULL, 0) != -1)
			;
		free_darr((void **)pipe_fd);
		return (1);
	}
	return (0);
}
