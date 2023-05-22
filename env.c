/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:25:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/22 14:00:01 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_data *data, char **argv)
{
	int		index_argv;
	int		index_env;

	index_argv = 0;
	while (argv[++index_argv])
	{
		index_env = 0;
		if (check_identifier(data, ft_strdup(argv[0]), argv[index_argv]))
			continue ;
		while (data->envp.envp[index_env] && \
		ft_strncmp(data->envp.envp[index_env][0], argv[index_argv], \
		ft_strlen(argv[index_argv]) + 1))
			index_env++;
		if (data->envp.envp[index_env])
		{
			free_darr((void **)data->envp.envp[index_env]);
			while (data->envp.envp[index_env + 1])
			{
				data->envp.envp[index_env] = data->envp.envp[index_env + 1];
				index_env++;
			}
			data->envp.envp[index_env] = NULL;
		}
	}
	if (!argv[1])
	{
		handle_error(data, argv[0], 0);
		return ;
	}
	data->exit_status = 0;
}

void	env(t_data *data, char **argv)
{
	int	i;

	i = 0;
	if (!data->envp.envp || argv[1])
	{
		data->exit_status = 1;
		return ;
	}
	while (data->envp.envp[i] != NULL)
	{
		if (data->envp.envp[i][1])
			printf("%s=%s\n", data->envp.envp[i][0], data->envp.envp[i][1]);
		i++;
	}
	data->exit_status = 0;
}

char	*get_env_var(t_data *data, const char *var_name)
{
	int		index;
	char	*var_value;

	index = 0;
	var_value = 0;
	while (data->envp.envp[index] && ft_strncmp(data->envp.envp[index][0], \
		var_name, ft_strlen(data->envp.envp[index][0]) + 1))
		index++;
	if (data->envp.envp[index])
		var_value = data->envp.envp[index][1];
	return (var_value);
}
