/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:36:35 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/03 00:14:50 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_data *data, int *pipes)
{
	int		id;
	pid_t	pid;

	id = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		close(pipes[1]);
		find_command(data, data->s_argv[id]);
		exit(0);
	}
	else
	{
		while (data->s_argv[id + 1])
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(pipes[0], STDIN_FILENO);
				close(pipes[0]);
				close(pipes[1]);
				find_command(data, data->s_argv[++id]);
				exit(0);
			}
			id++;
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
		if (!ft_strncmp(argv[i], "|", 2))
			count++;
		if (count == id && ft_strncmp(argv[i], "|", 2))
		{
			k++;
		}
		i++;
	}
	return (k);
}

void	get_s_argv(t_data *data)
{
	int		i;
	int		k;
	int		count;

	i = 0;
	count = 1;
	set_argv(data);
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
	int		pipes[2];
	char	*argv;

	if (!data->prompt)
		return (0);
	argv = ft_strchr(data->prompt, '|');
	if (argv)
	{
		pipe(pipes);
		create_pipes(data, pipes);
		close(pipes[0]);
		close(pipes[1]);
		waitpid(-1, NULL, 0);
		return (1);
	}
	return (0);
}
