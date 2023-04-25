/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:25:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/25 19:01:34 by bsilva-c         ###   ########.fr       */
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

char	*get_env_var(t_data *data)
{
	char	*res;
	char	*var;
	char	**arguments;

	arguments = ft_split(data->prompt, ' ');
	var = ft_strtrim(arguments[0], "$");
	res = getenv(var);
	free_darr((void **)arguments);
	free(var);
	data->exit_status = 0;
	return (res);
}
