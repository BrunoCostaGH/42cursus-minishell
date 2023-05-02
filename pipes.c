/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:36:35 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/02 19:34:55 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_data *data, int id)
{
	int		pipes[2];
	pid_t	pid;

	pipe(pipes);
	pid = fork();
	//ft_printf("%i, %s\n", pid, data->s_argv[id][0]);
	dup2(pipes[0], STDIN_FILENO);
	dup2(pipes[1], STDOUT_FILENO);
	if (pid == 0)
	{
		close(pipes[0]);
		find_command(data, data->s_argv[id]);
		close(pipes[1]);
		//fprintf(stderr, "Failed to execute '%s'\n", firstcmd);
		exit(0);
	}
	else
	{
		close(pipes[1]);
		find_command(data, data->s_argv[id + 1]);
		close(pipes[0]);
		//fprintf(stderr, "Executed\n");
	}
	close(0);
	close(1);
}

/*void	ft_last(t_data *data, int id, int prevpipe)
{
	pid_t	cpid;

	cpid = fork ();
	if (cpid == 0)
	{
		dup2 (prevpipe, STDIN_FILENO);
		close (prevpipe);
		find_command(data, data->s_argv[id]);
		exit(0);
	}
	else
	{
		close (prevpipe);
		while (wait (NULL) != -1)
			;
	}
}

void	ft_pipe(t_data *data, int id, int *prevpipe)
{
	int		pipefd[2];
	pid_t	cpid;

	pipe (pipefd);
	cpid = fork ();
	if (cpid == 0)
	{
		close (pipefd[0]);
		dup2 (pipefd[1], STDOUT_FILENO);
		close (pipefd[1]);
		dup2 (*prevpipe, STDIN_FILENO);
		close (*prevpipe);
		find_command(data, data->s_argv[id]);
		exit(0);
	}
	else
	{
		close (pipefd[1]);
		close (*prevpipe);
		*prevpipe = pipefd[0];
	}
}

int 	create_pipes(t_data *data, int id)
{
	int	prevpipe;

	prevpipe = dup (0);
	while (data->s_argv[id])
	{
		if (data->s_argv[id] != NULL)
			ft_pipe (data, id, &prevpipe);
		else if (data->s_argv[id + 1] == NULL)
			ft_last (data, id, prevpipe);
		id++;
	}
	return (0);
}*/


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
	char	*argv;

	if (!data->prompt)
		return (0);
	argv = ft_strchr(data->prompt, '|');
	if (argv)
		return (1);
	return (0);
}
