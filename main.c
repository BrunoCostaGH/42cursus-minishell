/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:03:13 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/02 17:52:14 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_command(t_data *data, char **argv)
{
	if (argv && *argv)
	{
		if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])))
			shell_exit(data);
		else if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
			change_dir(data, argv);
		else if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
			pwd(data);
		else if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
			env(data);
		else if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
			echo(data, argv);
		else if (!ft_strncmp(argv[0], "unset", ft_strlen(argv[0])))
			unset(data, argv);
		else if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
			export(data, argv);
		else
			run_executable(data, argv);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = init_struct(envp);
	set_handle_struct();
	execute_sig_action(0, data);
	(void)ac;
	(void)av;
	while (1)
	{
		data->prompt = readline("\x1B[1;32m(Minishell)$ \x1B[0m");
		if (data->prompt == NULL)
		{
			printf("\n");
			shell_exit(data);
		}
		if (data->prompt && *data->prompt)
			add_history(data->prompt);
		set_argv(data);
		find_command(data, data->argv);
		free_darr((void **)data->argv);
		data->argv = 0;
	}
}
