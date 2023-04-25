/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:03:13 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/25 18:49:34 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = init_struct(envp);
	(void)ac;
	(void)av;
	while (1)
	{
		data->prompt = readline("\x1B[1;32m(Minishell)$ \x1B[0m");
		if (!ft_strncmp(data->prompt, "exit", ft_strlen("exit")))
			shell_exit(data);
		else if (!ft_strncmp(data->prompt, "cd", ft_strlen("cd")))
			change_dir(data);
		else if (!ft_strncmp(data->prompt, "pwd", ft_strlen("pwd")))
			pwd(data);
		else if (!ft_strncmp(data->prompt, "$?", ft_strlen("$?")))
			get_exit_status(data);
		else if (!ft_strncmp(data->prompt, "$", ft_strlen("$")))
			get_env_var(data);
		else if (!ft_strncmp(data->prompt, "env", ft_strlen("env")))
			env(data->envp);
		else
			run_executable(data);
		if (*data->prompt)
			add_history(data->prompt);
	}
}
