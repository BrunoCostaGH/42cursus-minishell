/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:25:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/02 14:58:15 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_data *data, char **argv)
{
	int		argv_count;
	int		env_count;
	int		index_argv;
	int		index_env;
	char	**temp_envp;

	argv_count = 0;
	env_count = 0;
	index_argv = 0;
	index_env = 0;
	if (!*argv[1] || !ft_strrchr(argv[1], '='))
		return ;
	while (argv[argv_count])
		argv_count++;
	while (data->envp[env_count])
		env_count++;
	temp_envp = ft_calloc(argv_count + env_count + 1, sizeof(char *));
	while (data->envp[index_env])
	{
		temp_envp[index_env] = data->envp[index_env];
		index_env++;
	}
	while (argv[++index_argv])
		temp_envp[index_env++] = ft_strdup(argv[index_argv]);
	free(data->envp);
	data->envp = temp_envp;
}

void	unset(t_data *data, char **argv)
{
	int		index_argv;
	int		index_env;
	char	*name;

	index_argv = 0;
	index_env = 0;
	while (argv[++index_argv])
	{
		name = ft_strjoin(argv[index_argv], "=");
		while (data->envp[index_env] && ft_strncmp(data->envp[index_env], \
			name, ft_strlen(name)))
			index_env++;
		if (data->envp[index_env])
		{
			free(data->envp[index_env]);
			data->envp[index_env] = 0;
			if (data->envp[index_env + 1])
			{
				while (data->envp[index_env + 1])
				{
					data->envp[index_env] = data->envp[index_env + 1];
					index_env++;
				}
				data->envp[index_env] = NULL;
			}
		}
		free(name);
	}
	data->exit_status = 0;
}

void	env(t_data *data)
{
	int	i;

	i = 0;
	if (!data->envp)
	{
		data->exit_status = 1;
		return ;
	}
	while (data->envp[i] != NULL)
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
	data->exit_status = 0;
}

char	*get_env_var(t_data *data, const char *var_name)
{
	int		index;
	char	*var_value;

	index = 0;
	var_value = NULL;
	var_name = var_name + 1;
	while (data->envp[index] && ft_strncmp(data->envp[index], \
		var_name, ft_strlen(var_name)))
		index++;
	if (data->envp[index])
		var_value = ft_strrchr(data->envp[index], '=') + 1;
	return (var_value);
}
