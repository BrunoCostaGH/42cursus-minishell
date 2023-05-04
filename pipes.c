/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:36:35 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/04 14:17:39 by bsilva-c         ###   ########.fr       */
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
		find_command(data, data->s_argv[id]);
		exit(0);
	}
	else
	{
		while (data->s_argv[++id])
		{
			if (data->s_argv[id + 1])
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
				find_command(data, data->s_argv[id]);
				exit(0);
			}
		}
	}
}

int	count_args(char **argv, int id)
{
	int	i;
	int	k;
	int	count;

	i = 0;
	k = 0;
	count = 0;
	while (argv && argv[i])
	{
		if (!ft_strncmp(argv[i], "| ", 2))
			count++;
		if (count == id && ft_strncmp(argv[i], "| ", 2))
			k++;
		i++;
	}
	return (k);
}

void	set_s_argv(t_data *data)
{
	int		i;
	int		k;
	int		count;

	i = 0;
	count = 2;
	while (data->argv && data->argv[i])
	{
		if (!ft_strncmp(data->argv[i], "|", 2))
			count++;
		i++;
	}
	data->n_of_pipes = count;
	data->s_argv = ft_calloc(count + 1, sizeof(char **));
	i = 0;
	k = 0;
	count = count_args(data->argv, k);
	data->s_argv[k] = ft_calloc(count + 1, sizeof(char *));
	count = 0;
	while (data->argv && data->argv[i])
	{
		if (ft_strncmp(data->argv[i], "|", 2))
		{
			data->s_argv[k][count] = data->argv[i];
			count++;
		}
		else
		{
			k++;
			count = count_args(data->argv, k);
			data->s_argv[k] = ft_calloc(count + 1, sizeof(char *));
			count = 0;
		}
		i++;
	}
}

int	check_for_pipes(t_data *data)
{
	int		**pipe_fd;
	int		pipe_amount;

	if (!data->prompt)
		return (0);
	set_s_argv(data);
	pipe_amount = 0;
	while (data->s_argv[pipe_amount + 1])
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
