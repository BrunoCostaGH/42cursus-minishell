/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:31:46 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/18 20:27:57 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_argv(t_data *data, char **argv)
{
	int	i;

	i = 0;
	if (!argv[1])
	{
		printf("exit\n");
		return (data->exit_status);
	}
	if (argv[2])
	{
		write(2, "exit: too many arguments\n", 25);
		data->exit_status = 1;
		return (data->exit_status);
	}
	printf("exit\n");
	while (argv[1][i])
	{
		if (ft_isalpha(argv[1][i++]))
		{
			write(2, "exit: numeric argument required\n", 32);
			data->exit_status = 2;
		}
	}
	return (data->exit_status);
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
	free(data->argv.type);
	data->argv.args = 0;
	data->argv.type = 0;
}

void	shell_exit(t_data *data, char **argv)
{
	int	i;
	int	exit_status;

	if (argv && check_argv(data, argv) == 1)
		return ;
	rl_clear_history();
	if (data->prompt)
		free(data->prompt);
	if (data->argv.args)
		argv_clear(data);
	i = 0;
	if (data->envp)
	{
		while (data->envp[i])
			free_darr((void **) data->envp[i++]);
		free(data->envp);
	}
	exit_status = data->exit_status;
	free(data);
	exit(exit_status);
}
