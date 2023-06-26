/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:14:23 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/26 23:32:21 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_existing_env(t_data *data, char **argv, int *index, int index_argv)
{
	int		status;
	char	**temp;

	status = 0;
	temp = ft_split(argv[index_argv], '=');
	if (temp[0] && data->envp.envp[*index])
	{
		if (temp[1])
		{
			free(data->envp.envp[*index][1]);
			data->envp.envp[*index][1] = ft_strdup(temp[1]);
		}
		else if (ft_strchr(argv[index_argv], '='))
		{
			free(data->envp.envp[*index][1]);
			data->envp.envp[*index][1] = ft_calloc(1, sizeof(char));
		}
		status = 1;
	}
	free_darr((void **)temp);
	return (status);
}

int	check_envp(t_data *data, char **argv)
{
	int		i;
	int		index_argv;
	int		amount_edited;
	char	**temp;

	amount_edited = 0;
	index_argv = 0;
	while (argv[++index_argv])
	{
		i = 0;
		temp = ft_split(argv[index_argv], '=');
		while (*temp && data->envp.envp[i] && ft_strncmp(data->envp.envp[i][0], \
		temp[0], ft_strlen(data->envp.envp[i][0]) + 1))
			i++;
		amount_edited += set_existing_env(data, argv, &i, index_argv);
		free_darr((void **)temp);
	}
	return (amount_edited);
}

static void	create_slot(char ***envp, int index_slot)
{
	int		index_sorted;
	char	**temp;

	index_sorted = index_slot;
	while (envp[index_sorted])
	{
		temp = envp[index_sorted + 1];
		envp[index_sorted + 1] = envp[index_slot];
		envp[index_slot] = temp;
		index_sorted++;
	}
}

void	build_sorted_env(t_data *data, char ***envp)
{
	int		index_envp;
	int		index_sorted;

	index_envp = 0;
	while (data->envp.envp[index_envp])
	{
		index_sorted = 0;
		while (envp[index_sorted] && \
		ft_strncmp(envp[index_sorted][0], data->envp.envp[index_envp][0], \
		ft_strlen(envp[index_sorted][0])) < 0)
			index_sorted++;
		create_slot(envp, index_sorted);
		envp[index_sorted] = ft_calloc(2 + 1, sizeof(char *));
		if (!envp[index_sorted])
			return ;
		envp[index_sorted][0] = ft_strdup(data->envp.envp[index_envp][0]);
		if (data->envp.envp[index_envp][1])
			envp[index_sorted][1] = ft_strdup(data->envp.envp[index_envp][1]);
		index_envp++;
	}
}

char	***duplicate_envp(t_data *data, int len)
{
	int		i;
	char	***temp_envp;

	i = 0;
	temp_envp = ft_calloc(len + darr_len((void **) data->envp.envp) + 1, \
	sizeof(char **));
	if (!temp_envp)
		return (0);
	while (data->envp.envp[i])
	{
		temp_envp[i] = ft_calloc(2 + 1, sizeof(char *));
		if (!temp_envp[i])
			return (0);
		temp_envp[i][0] = ft_strdup(data->envp.envp[i][0]);
		if (data->envp.envp[i][1])
			temp_envp[i][1] = ft_strdup(data->envp.envp[i][1]);
		free_darr((void **)data->envp.envp[i]);
		i++;
	}
	return (temp_envp);
}
