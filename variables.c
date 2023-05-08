/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:16:07 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/05 19:33:37 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env_var(t_data *data, int id, int i)
{
	int		k;
	char	*temp;
	char	*env_var;
	char	*var_name;

	temp = ft_strnstr(data->argv.args[id][i], "$", \
		ft_strlen(data->argv.args[id][i]));
	k = 1;
	while (temp[++k])
	{
		if (!(ft_isalnum(temp[k]) || temp[k] == '_'))
			break ;
	}
	var_name = ft_calloc(k + 1, sizeof(char));
	ft_strlcpy(var_name, temp, k + 1);
	env_var = get_env_var(data, var_name);
	if (!env_var)
		env_var = "(null)";
	temp = ft_fndnrepl(data->argv.args[id][i], var_name, env_var);
	free(data->argv.args[id][i]);
	data->argv.args[id][i] = temp;
	free(var_name);
}

static void	set_exit_status(t_data *data, int id, int i)
{
	char	*temp;

	temp = ft_fndnrepl(data->argv.args[id][i], "$?", \
	ft_itoa(data->exit_status));
	free(data->argv.args[id][i]);
	data->argv.args[id][i] = temp;
}

void	check_variables(t_data *data)
{
	int	i;
	int	id;

	id = 0;
	while (data->argv.args && data->argv.args[id])
	{
		i = 0;
		while (data->argv.args[id][i])
		{
			if (data->argv.args[id][i][0] != 39)
			{
				if (ft_strnstr(data->argv.args[id][i], "$?", \
					ft_strlen(data->argv.args[id][i])))
				{
					set_exit_status(data, id, i);
					continue ;
				}
				if (ft_strnstr(data->argv.args[id][i], "$", \
					ft_strlen(data->argv.args[id][i])) && \
					data->argv.args[id][i][1])
				{
					set_env_var(data, id, i);
					continue ;
				}
			}
			i++;
		}
		id++;
	}
}
