/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:15 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/05 19:24:47 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envp(t_data *data, char **envp)
{
	int		len;
	char	**temp;

	len = 0;
	while (envp[len])
		len++;
	data->envp.sorted_envp = 0;
	data->envp.exec_envp = 0;
	data->envp.envp = ft_calloc(len + 1, sizeof(char **));
	if (!data->envp.envp)
		return ;
	while (len-- > 0)
	{
		temp = ft_split(envp[len], '=');
		data->envp.envp[len] = ft_calloc(2 + 1, sizeof(char *));
		if (!data->envp.envp[len])
			return ;
		data->envp.envp[len][0] = ft_strdup(temp[0]);
		if (temp[1])
			data->envp.envp[len][1] = ft_strdup(temp[1]);
		free_darr((void **)temp);
	}
}

int	init_pipe_child(t_data *data)
{
	int	pipe_index;

	pipe_index = 0;
	while (data->pipe_fd[pipe_index])
		pipe_index++;
	data->pipe_fd[pipe_index] = ft_calloc(2 + 1, sizeof(int));
	if (!data->pipe_fd[pipe_index])
		return (1);
	pipe(data->pipe_fd[pipe_index]);
	return (0);
}

static void	delete_tmp_file(t_data *data)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		clear_temp(data);
		exit_shell(data, 0);
	}
	waitpid(pid, 0, 0);
	free(data->tmp_file);
}

void	init_tmp(t_data *data)
{
	int		i;
	char	*temp;

	i = 1;
	if (data->tmp_file)
		delete_tmp_file(data);
	data->tmp_file = ft_strdup(".tmp1");
	while (access(data->tmp_file, 0) == 0)
	{
		if (data->tmp_file)
			free(data->tmp_file);
		temp = ft_itoa(++i);
		data->tmp_file = ft_strjoin(".tmp", temp);
		free(temp);
	}
}

void	*init_struct(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->file_io = ft_calloc(2 + 1, sizeof(int));
	if (!data->file_io)
		return (0);
	data->std_io = ft_calloc(2 + 1, sizeof(int));
	if (!data->std_io)
		return (0);
	data->std_io[0] = dup(0);
	data->std_io[1] = dup(1);
	data->interactive = TRUE;
	data->exit_status = 0;
	data->prompt = 0;
	data->argv.args = 0;
	data->argv.type = 0;
	data->tmp_file = 0;
	init_envp(data, envp);
	return (data);
}
