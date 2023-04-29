/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:25:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/27 15:06:29 by bsilva-c         ###   ########.fr       */
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

char	*get_env_var(char *data)
{
	char	*res;
	char	*var;

	var = ft_strtrim(data, "$");
	res = getenv(var);
	free(var);
	return (res);
}
