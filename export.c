/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:42:05 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:14 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_sorted_envp(t_data *data)
{
	int	id;

	if (data->envp.sorted_envp)
	{
		id = 0;
		while (data->envp.sorted_envp[id])
			free_darr((void **)data->envp.sorted_envp[id++]);
		free(data->envp.sorted_envp);
		data->envp.sorted_envp = 0;
	}
}

static int	check_argv(t_data *data, char *arg, int initial)
{
	int		index;

	index = 0;
	if (initial == TRUE && !arg)
	{
		clear_sorted_envp(data);
		data->envp.sorted_envp = ft_calloc(\
		darr_len((void **)data->envp.envp) + 1, sizeof(char **));
		if (!data->envp.sorted_envp)
			return (1);
		build_sorted_env(data, data->envp.sorted_envp);
		while (data->envp.sorted_envp[++index - 1])
		{
			printf("declare -x %s", data->envp.sorted_envp[index - 1][0]);
			if (data->envp.sorted_envp[index - 1][1])
				printf("=\"%s\"", data->envp.sorted_envp[index - 1][1]);
			printf("\n");
		}
		return (1);
	}
	else if (initial == FALSE)
		if (check_identifier(data, "export", arg))
			return (1);
	return (0);
}

static void	do_export(t_data *data, char ***temp_envp, char **argv)
{
	int		index_argv;
	int		index_env;
	char	**temp;

	index_argv = 0;
	index_env = darr_len((void **) temp_envp);
	while (argv[++index_argv])
	{
		temp = ft_split(argv[index_argv], '=');
		if (check_argv(data, temp[0], FALSE))
		{
			free_darr((void **)temp);
			continue ;
		}
		temp_envp[index_env] = ft_calloc(2 + 1, sizeof(char *));
		if (!temp_envp[index_env])
			return ;
		temp_envp[index_env][0] = ft_strdup(temp[0]);
		if (temp[1])
			temp_envp[index_env][1] = ft_strdup(temp[1]);
		else if (ft_strchr(argv[index_argv], '='))
			temp_envp[index_env][1] = ft_calloc(1, sizeof(char));
		free_darr((void **)temp);
		index_env++;
	}
}

void	export(t_data *data, char **argv)
{
	int		index_argv;
	char	***temp_envp;

	if (check_argv(data, argv[1], TRUE))
		return ;
	index_argv = darr_len((void **)argv) - check_envp(data, argv);
	data->exit_status = 0;
	if (!index_argv)
		return ;
	temp_envp = duplicate_envp(data, index_argv);
	do_export(data, temp_envp, argv);
	free(data->envp.envp);
	data->envp.envp = temp_envp;
}
