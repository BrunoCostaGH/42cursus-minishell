/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_n_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 23:12:22 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/25 00:22:31 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_argv(t_data *data, int id)
{
	int	i;
	int	k;

	i = id - 1;
	while (data->argv.type[i++])
		data->argv.type[i - 1] = data->argv.type[i];
	i = id;
	k = 0;
	free(data->argv.args[i][k]);
	data->argv.args[i][k] = 0;
	while (data->argv.args[i][k++ + 1])
		data->argv.args[i][k - 1] = data->argv.args[i][k];
	data->argv.args[i][k - 1] = 0;
	if (!data->argv.args[i][0])
	{
		free(data->argv.args[i]);
		data->argv.args[i] = 0;
		while (data->argv.args[i++ + 1])
			data->argv.args[i - 1] = data->argv.args[i];
		data->argv.args[i - 1] = 0;
	}
}

int	get_fd_out(t_data *data, int *fd)
{
	int	id;

	id = 0;
	while (data->argv.type[id])
	{
		if (!data->argv.args[id + 1][0])
		{
			write(2, &"Error: syntax error near unexpected token\n", 42);
			return (1);
		}
		if (data->argv.type[id] == REDR_OUTPUT)
		{
			if (*fd)
				close(*fd);
			*fd = open(data->argv.args[id + 1][0], O_CREAT | O_RDWR | \
			O_TRUNC, S_IRWXU);
			clear_argv(data, id + 1);
			continue ;
		}
		else if (data->argv.type[id] == REDR_APPEND)
		{
			if (*fd)
				close(*fd);
			*fd = open(data->argv.args[id + 1][0], O_CREAT | O_RDWR | \
			O_APPEND, S_IRWXU);
			clear_argv(data, id + 1);
			continue ;
		}
		if (*fd == -1)
			shell_error();
		id++;
	}
	return (0);
}
