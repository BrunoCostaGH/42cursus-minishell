/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:15 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/26 23:11:21 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envp(t_data *data, char **envp)
{
	int		len;
	char	**temp;

	len = 0;
	while (envp[len])
		len++;
	data->envp.exec_envp = 0;
	data->envp.envp = malloc(sizeof(char **) * len + 1);
	if (!data->envp.envp)
		return ;
	while (len-- > 0)
	{
		temp = ft_split(envp[len], '=');
		data->envp.envp[len] = ft_calloc(2, sizeof(char *));
		if (!data->envp.envp[len])
			return ;
		data->envp.envp[len][0] = temp[0];
		data->envp.envp[len][1] = temp[1];
		free(temp);
	}
}

void	init_tmp(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (i == 0 || access(temp, F_OK) == 0)
	{
		if (data->tmp_file)
			free(data->tmp_file);
		data->tmp_file = ft_strjoin(".tmp", ft_itoa(++i));
	}
}

void	*init_struct(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->interactive = TRUE;
	data->exit_status = 0;
	data->prompt = NULL;
	data->argv.args = NULL;
	data->argv.type = NULL;
	init_envp(data, envp);
	init_tmp(data);
	return (data);
}
