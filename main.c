/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:03:13 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/27 17:46:25 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		data->argv = set_argv(data->prompt);
		check_variables(data);
		if (!ft_strncmp(data->prompt, "exit", ft_strlen("exit")))
			shell_exit(data);
		else if (!ft_strncmp(data->prompt, "cd", ft_strlen("cd")))
			change_dir(data);
		else if (!ft_strncmp(data->prompt, "pwd", ft_strlen("pwd")))
			pwd(data);
		else if (!ft_strncmp(data->prompt, "env", ft_strlen("env")))
			env(data);
		else if (!ft_strncmp(data->prompt, "echo", ft_strlen("echo")))
			echo(data);
		else
			run_executable(data, data->argv);
		if (*data->prompt)
			add_history(data->prompt);
		free_darr((void **)data->argv);
		data->argv = 0;
	}
}
