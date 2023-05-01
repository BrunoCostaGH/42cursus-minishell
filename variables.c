/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:16:07 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/01 15:31:27 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env_var(t_data *data, int i)
{
	int		k;
	char	*temp;
	char	*env_var;
	char	*var_name;

	temp = ft_strnstr(data->argv[i], "$", ft_strlen(data->argv[i]));
	k = 1;
	while (temp[++k])
	{
		if (!(ft_isalnum(temp[k]) || temp[k] == '_'))
			break ;
	}
	var_name = ft_calloc(k + 1, sizeof(char));
	ft_strlcpy(var_name, temp, k + 1);
	env_var = get_env_var(var_name);
	if (!env_var)
		env_var = "(null)";
	temp = ft_fndnrepl(data->argv[i], var_name, env_var);
	free(data->argv[i]);
	data->argv[i] = temp;
	free(var_name);
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
			if (ft_strnstr(data->argv[i], "$", ft_strlen(data->argv[i])) \
				&& data->argv[i][1])
			{
				set_env_var(data, i);
				continue ;
			}
		}
		i++;
	}
}
