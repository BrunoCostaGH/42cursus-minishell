/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:31:46 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/24 17:00:55 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_argv(t_data *data, char **argv)
{
	int	i;

	i = 0;
	while (argv[1] && argv[1][i])
		if (ft_isalpha(argv[1][i++]))
			return (handle_error(data, argv[0], 4));
	if (argv[1] && argv[2])
		return (handle_error(data, argv[0], 2));
	return (0);
}

static void	clear_temp(t_data *data)
{
	if (access(data->tmp_file, F_OK) == 0)
	{
		clear_argv(data);
		data->prompt = ft_strjoin("rm ", data->tmp_file);
		set_argv(data);
		find_command(data, data->argv.args[0]);
	}
	free(data->tmp_file);
	data->tmp_file = 0;
}

static void	clear_envp(t_data *data)
{
	int	id;

	if (!data->envp.envp)
		return ;
	id = 0;
	while (data->envp.envp[id])
		free_darr((void **)data->envp.envp[id++]);
	free(data->envp.envp);
	data->envp.envp = 0;
	if (data->envp.sorted_envp)
	{
		id = 0;
		while (data->envp.sorted_envp[id])
			free_darr((void **)data->envp.sorted_envp[id++]);
		free(data->envp.sorted_envp);
		data->envp.sorted_envp = 0;
	}
	if (data->envp.exec_envp)
		free_darr((void **)data->envp.exec_envp);
}

void	clear_argv(t_data *data)
{
	int	id;

	id = 0;
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = 0;
	}
	if (!data->argv.args)
		return ;
	while (data->argv.args[id])
		free_darr((void **)data->argv.args[id++]);
	free(data->argv.args);
	data->argv.args = 0;
	if (data->argv.type)
	{
		free(data->argv.type);
		data->argv.type = 0;
	}
}

void	exit_shell(t_data *data, char **argv)
{
	int	exit_status;
	int	check_return;

	check_return = 0;
	if (argv)
	{
		printf("exit\n");
		check_return = check_argv(data, argv);
	}
	if (check_return == 1)
		return ;
	else if (argv && argv[1] && check_return != 2)
		exit_status = ft_atoi(argv[1]);
	else
		exit_status = data->exit_status;
	rl_clear_history();
	free(data->file_io);
	free(data->std_io);
	if (data->tmp_file)
		clear_temp(data);
	clear_argv(data);
	clear_envp(data);
	free(data);
	exit(exit_status);
}
