/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:16:07 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/28 19:28:36 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env_var(t_data *data, int i)
{
	char	*temp;
	char	*env_var;
	char	**temp_split;

	temp = ft_strnstr(data->argv[i], "$", ft_strlen(data->argv[i]));
	temp_split = ft_split(temp, ' ');
	temp = ft_strtrim(temp_split[0], "'\"");
	env_var = get_env_var(temp);
	free(temp);
	if (env_var)
		temp = env_var;
	else
		temp = "(null)";
	temp = ft_fndnrepl(data->argv[i], temp_split[0], temp);
	free(data->argv[i]);
	data->argv[i] = temp;
	free_darr((void **)temp_split);
}

static void	set_exit_status(t_data *data, int i)
{
	char	*temp;

	temp = ft_fndnrepl(data->argv[i], "$?", ft_itoa(data->exit_status));
	free(data->argv[i]);
	data->argv[i] = temp;
}

void	check_variables(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i])
	{
		if (data->argv[i][0] != 39)
		{
			if (ft_strnstr(data->argv[i], "$?", ft_strlen(data->argv[i])))
			{
				set_exit_status(data, i);
				continue ;
			}
			if (ft_strnstr(data->argv[i], "$", ft_strlen(data->argv[i])))
			{
				set_env_var(data, i);
				continue ;
			}
		}
		i++;
	}
}
