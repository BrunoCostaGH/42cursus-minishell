/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:15 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/18 16:17:31 by bsilva-c         ###   ########.fr       */
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
	data->envp = ft_calloc(len + 1, sizeof(char **));
	if (!data->envp)
		return ;
	while (len-- > 0)
	{
		data->envp[len] = malloc(sizeof(char *) * 2);
		temp = ft_split(envp[len], '=');
		data->envp[len][0] = temp[0];
		data->envp[len][1] = temp[1];
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
