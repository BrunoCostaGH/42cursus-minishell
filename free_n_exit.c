/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:31:46 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/26 00:16:59 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_argv(t_data *data, char **argv)
{
	int	i;

	i = 0;
	if (argv[1] && argv[2])
		return (handle_error(data, argv[0], 1));
	while (argv[1] && argv[1][i])
		if (ft_isalpha(argv[1][i++]))
			return (handle_error(data, argv[0], 3));
	if (!argv[1])
		printf("exit\n");
	return (0);
}

static void	envp_clear(t_data *data)
{
	int	id;

	id = 0;
	while (data->envp.envp && data->envp.envp[id])
		free_darr((void **)data->envp.envp[id++]);
	free(data->envp.envp);
	data->envp.envp = 0;
	if (data->envp.exec_envp)
		free_darr((void **) data->envp.exec_envp);
}

void	argv_clear(t_data *data)
{
	int	id;

	id = 0;
	if (!data->argv.args)
		return ;
	while (data->argv.args && data->argv.args[id])
		free_darr((void **)data->argv.args[id++]);
	free(data->argv.args);
	data->argv.args = 0;
	if (data->argv.type)
	{
		free(data->argv.type);
		data->argv.type = 0;
	}
}

void	shell_error(void)
{
	perror("Error");
	exit(1);
}

void	shell_exit(t_data *data, char **argv)
{
	int	exit_status;

	if (argv && check_argv(data, argv) == 1)
		return ;
	exit_status = data->exit_status;
	rl_clear_history();
	if (access(data->tmp_file, F_OK) == 0)
	{
		if (data->prompt)
			free(data->prompt);
		argv_clear(data);
		data->prompt = ft_strjoin("rm ", data->tmp_file);
		set_argv(data);
		find_command(data, data->argv.args[0]);
	}
	if (data->prompt)
		free(data->prompt);
	argv_clear(data);
	envp_clear(data);
	free(data);
	exit(exit_status);
}
