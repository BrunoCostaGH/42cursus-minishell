/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:36:35 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/27 13:43:02 by bsilva-c         ###   ########.fr       */
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

void	here_doc(t_data *data, int *fd, int id)
{
	char	*str;

	*fd = open(data->tmp_file, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	if (*fd == -1)
	{
		perror("Error");
		data->exit_status = 1;
	}
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
	{
		perror("Error");
		data->exit_status = 1;
	}
}

void	create_pipes(t_data *data, int **pipe_fd, int *pid)
{
	int		id;
	int		fd_in;
	int		fd_out;

	id = 0;
	fd_in = 0;
	fd_out = 0;
	if (get_fd_out(data, &fd_out) == 1)
		return ;
	while (!data->argv.args[id][0])
		id++;
	pipe_fd[id] = malloc(sizeof(int) * 2);
	if (!pipe_fd[id])
		return ;
	pipe(pipe_fd[id]);
	*pid = fork();
	if (*pid == 0)
	{
		init_tmp(data);
		data->exit_status = 0;
		if (data->argv.type[id] == REDR_DELIM)
		{
			here_doc(data, &fd_in, id++);
			dup2(fd_in, STDIN_FILENO);
		}
		else if (data->argv.type[id] == REDR_INPUT)
		{
			fd_in = open(data->argv.args[id + 1][0], O_RDONLY);
			if (fd_in == -1)
			{
				perror("Error");
				data->exit_status = 1;
				free_darr((void **)pipe_fd);
				shell_exit(data, 0);
			}
			dup2(fd_in, STDIN_FILENO);
		}
		if (data->argv.type[id] == PIPE)
			dup2(pipe_fd[id][1], STDOUT_FILENO);
		else if (fd_out)
			dup2(fd_out, STDOUT_FILENO);
		close_pipes(pipe_fd, id);
		if (id > 0 && data->argv.type[id - 1] == REDR_DELIM)
			find_command(data, data->argv.args[id - 1]);
		else
			find_command(data, data->argv.args[id]);
		free_darr((void **)pipe_fd);
		shell_exit(data, 0);
	}
	else
	{
		while (data->argv.args[++id])
		{
			if (data->argv.type[id - 1] != PIPE)
				continue ;
			if (data->argv.type[id] == PIPE)
			{
				pipe_fd[id] = malloc(sizeof(int) * 2);
				if (!pipe_fd[id])
					return ;
				pipe(pipe_fd[id]);
			}
			*pid = fork();
			if (*pid == 0)
			{
				init_tmp(data);
				data->exit_status = 0;
				if (data->argv.type[id] == REDR_DELIM)
				{
					here_doc(data, &fd_in, id++);
					dup2(fd_in, STDIN_FILENO);
				}
				else if (data->argv.type[id] == REDR_INPUT)
				{
					fd_in = open(data->argv.args[id + 1][0], O_RDONLY);
					if (fd_in == -1)
					{
						perror("Error");
						data->exit_status = 1;
						free_darr((void **)pipe_fd);
						shell_exit(data, 0);
					}
					dup2(fd_in, STDIN_FILENO);
				}
				else if (id > 1 && data->argv.type[id - 2] == REDR_DELIM)
					dup2(pipe_fd[id - 2][0], STDIN_FILENO);
				else
					dup2(pipe_fd[id - 1][0], STDIN_FILENO);
				if (pipe_fd[id])
					dup2(pipe_fd[id][1], STDOUT_FILENO);
				else if (fd_out)
					dup2(fd_out, STDOUT_FILENO);
				close_pipes(pipe_fd, id);
				if (data->argv.type[id - 1] == REDR_DELIM)
					find_command(data, data->argv.args[id - 1]);
				else
					find_command(data, data->argv.args[id]);
				free_darr((void **)pipe_fd);
				shell_exit(data, 0);
			}
		}
	}
}

int	check_for_pipes(t_data *data)
{
	int		i;
	int		pid;
	int		**pipe_fd;
	int		pipe_amount;

	if (!data->argv.args)
		return (0);
	i = 0;
	pipe_amount = 0;
	while (data->argv.type[i++])
			pipe_amount++;
	if (pipe_amount)
	{
		pipe_fd = ft_calloc(pipe_amount + 1, sizeof(int *));
		if (!pipe_fd)
			return (0);
		create_pipes(data, pipe_fd, &pid);
		close_pipes(pipe_fd, pipe_amount);
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
