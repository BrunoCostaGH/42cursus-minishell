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
