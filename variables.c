/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:16:07 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/27 15:06:02 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env_var(t_data *data, int i)
{
	char	*env_var;

	env_var = get_env_var(data->argv[i]);
	free(data->argv[i]);
	data->argv[i] = ft_strdup(env_var);
}

static void	set_exit_status(t_data *data, int i)
{
	free(data->argv[i]);
	data->argv[i] = ft_itoa(data->exit_status);
}

void	check_variables(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i])
	{
		if (!ft_strncmp(data->argv[i], "$?", ft_strlen("$?")))
			set_exit_status(data, i);
		if (!ft_strncmp(data->argv[i], "$", ft_strlen("$")))
			set_env_var(data, i);
		i++;
	}
}
