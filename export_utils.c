/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:14:23 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/26 23:10:46 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_existing_env(t_data *data, char **argv, int *index, int index_argv)
{
	int		status;
	char	**temp;

	status = 0;
	temp = ft_split(argv[index_argv], '=');
	if (data->envp.envp[*index])
	{
		free(data->envp.envp[*index][1]);
		data->envp.envp[*index][1] = 0;
		if (temp[1])
			data->envp.envp[*index][1] = ft_strdup(temp[1]);
		free(argv[index_argv]);
		*index = index_argv;
		while (argv[++*index])
			argv[*index - 1] = argv[*index];
		argv[--*index] = 0;
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

char	***duplicate_envp(t_data *data, int len)
{
	int		i;
	char	***temp_envp;

	i = 0;
	temp_envp = ft_calloc(len + len_darr((void **)data->envp.envp) + 1, \
	sizeof(char **));
	if (!temp_envp)
		return (0);
	while (data->envp.envp[i])
	{
		temp_envp[i] = ft_calloc(2, sizeof(char *));
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
