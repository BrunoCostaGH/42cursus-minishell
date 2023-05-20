/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:31:46 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/20 13:43:12 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_argv(t_data *data, char **argv)
{
	int	i;

	i = 0;
	if (!argv[1])
	{
		printf("exit\n");
		return (data->exit_status);
	}
	if (argv[2])
		return (handle_error(data, argv[0], 1));
	printf("exit\n");
	while (argv[1][i])
	{
		if (ft_isalpha(argv[1][i++]))
			return (handle_error(data, argv[0], 3));
	}
	return (data->exit_status);
}

static void	envp_clear(t_data *data)
{
	int	id;

	id = 0;
	while (data->envp.envp && data->envp.envp[id])
	{
		free_darr((void **)data->envp.envp[id]);
		data->envp.envp[id] = 0;
		id++;
	}
	free(data->envp.envp);
	data->envp.envp = 0;
	if (data->envp.exec_envp)
	{
		free_darr((void **) data->envp.exec_envp);
		data->envp.exec_envp = 0;
	}
}

void	argv_clear(t_data *data)
{
	int	id;

	id = 0;
	while (data->argv.args && data->argv.args[id])
	{
		free_darr((void **)data->argv.args[id]);
		data->argv.args[id] = 0;
		id++;
	}
	free(data->argv.args);
	data->argv.args = 0;
	if (data->argv.type)
	{
		free(data->argv.type);
		data->argv.type = 0;
	}
}

void	shell_exit(t_data *data, char **argv)
{
	int	exit_status;

	if (argv && check_argv(data, argv) == 1)
		return ;
	exit_status = data->exit_status;
	rl_clear_history();
	if (data->prompt)
		free(data->prompt);
	argv_clear(data);
	envp_clear(data);
	free(data);
	exit(exit_status);
}
