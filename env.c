/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:25:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/18 19:18:46 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_data *data, char **argv)
{
	int		index_argv;
	int		index_env;
	char	**temp;
	char	***temp_envp;

	index_env = 0;
	if (!argv[1])
	{
		while (data->envp[index_env])
		{
			printf("%s %s", "declare -x", data->envp[index_env][0]);
			if (data->envp[index_env][1])
				printf("=\"%s\"", data->envp[index_env][1]);
			printf("\n");
			index_env++;
		}
		return ;
	}
	index_argv = 0;
	while (argv[1][index_argv] && argv[1][index_argv] != '=')
	{
		if (!ft_isalpha(argv[1][index_argv]) && argv[1][index_argv] != '_')
		{
			write(2, "export: not a valid identifier\n", 31);
			data->exit_status = 1;
			return ;
		}
		index_argv++;
	}
	index_argv = 0;
	while (argv[index_argv])
		index_argv++;
	index_env = 0;
	while (data->envp[index_env])
		index_env++;
	temp_envp = ft_calloc(index_argv + index_env + 1, sizeof(char **));
	index_env = 0;
	while (data->envp[index_env])
	{
		temp_envp[index_env] = ft_calloc(2, sizeof(char *));
		temp_envp[index_env][0] = data->envp[index_env][0];
		temp_envp[index_env][1] = data->envp[index_env][1];
		index_env++;
	}
	index_argv = 0;
	while (argv[++index_argv])
	{
		temp = ft_split(argv[index_argv], '=');
		temp_envp[index_env] = ft_calloc(2, sizeof(char *));
		temp_envp[index_env][0] = ft_strdup(temp[0]);
		temp_envp[index_env][1] = ft_strdup(temp[1]);
		free_darr((void **)temp);
		index_env++;
	}
	free(data->envp);
	data->envp = temp_envp;
}

void	unset(t_data *data, char **argv)
{
	int		index_argv;
	int		index_env;

	index_argv = 0;
	index_env = 0;
	while (argv[++index_argv])
	{
		while (data->envp[index_env] && ft_strncmp(data->envp[index_env][0], \
			argv[index_argv], ft_strlen(argv[index_argv])))
			index_env++;
		if (data->envp[index_env])
		{
			free_darr((void **)data->envp[index_env]);
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
	}
	if (!argv[1])
	{
		write(2, "unset: not enough arguments\n", 24);
		data->exit_status = 1;
		return ;
	}
	data->exit_status = 0;
}

void	env(t_data *data, char **argv)
{
	int	i;

	i = 0;
	if (!data->envp || argv[1])
	{
		data->exit_status = 1;
		return ;
	}
	while (data->envp[i] != NULL)
	{
		if (data->envp[i][1])
			printf("%s=%s\n", data->envp[i][0], data->envp[i][1]);
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
	while (data->envp[index] && ft_strncmp(data->envp[index][0], \
		var_name, ft_strlen(var_name)))
		index++;
	if (data->envp[index])
		var_value = data->envp[index][1];
	return (var_value);
}
