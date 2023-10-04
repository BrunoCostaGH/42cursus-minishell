/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:03:13 by tabreia-          #+#    #+#             */
/*   Updated: 2023/09/28 19:54:20 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_command(t_data *data, char **argv)
{
	if (argv && *argv)
	{
		if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0]) + 1))
			exit_shell(data, argv);
		else if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0]) + 1))
			change_dir(data, argv);
		else if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0]) + 1))
			pwd(data);
		else if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0]) + 1))
			env(data, argv);
		else if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0]) + 1))
			echo(data, argv);
		else if (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0]) + 1))
			unset(data, argv);
		else if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0]) + 1))
			export(data, argv);
		else
			run_executable(data, argv);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data		*data;

	data = init_struct(envp);
	set_handle_struct();
	execute_sig_action(0, data);
	(void)ac;
	(void)av;
	while (1)
	{
		data->interactive = TRUE;
		data->prompt = ft_readline("\001\e[1;32m\002(Minishell)$ \001\e[0m\002");
		data->interactive = FALSE;
		if (data->prompt == NULL)
			data->prompt = ft_strdup("exit");
		if (data->prompt && *data->prompt)
			ft_add_history(data->prompt);
		set_argv(data);
		if (!check_tokens(data) && data->argv.args)
			find_command(data, *data->argv.args);
		clear_argv(data);
	}
}
