/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:15 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/19 18:18:41 by bsilva-c         ###   ########.fr       */
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
		data->envp.envp[len][0] = temp[0];
		data->envp.envp[len][1] = temp[1];
		free(temp);
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
	return (data);
}
