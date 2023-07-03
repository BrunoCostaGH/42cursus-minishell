/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:16:07 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/07/03 20:08:12 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_home_var(t_data *data, char **prompt)
{
	char	*temp;
	char	*env_var;

	env_var = get_env_var(data, "HOME");
	env_var = ft_strjoin(env_var, "/");
	if (!env_var)
		env_var = "";
	temp = ft_fndnrepl(*prompt, "~/", env_var);
	free(*prompt);
	*prompt = temp;
	free(env_var);
}

static void	set_exit_status(t_data *data, char **prompt)
{
	char	*value;
	char	*temp;

	value = ft_itoa(data->exit_status);
	temp = ft_fndnrepl(*prompt, "$?", value);
	free(*prompt);
	*prompt = temp;
	free(value);
}

static int	set_env_var(t_data *data, char **prompt)
{
	int		k;
	char	*temp;
	char	*env_var;
	char	*var_name;

	temp = find_variable(*prompt, "$", ft_strlen(*prompt));
	k = 0;
	while (temp && temp[++k])
		if (!(ft_isalnum(temp[k]) || temp[k] == '_'))
			break ;
	if (!temp || k == 1)
		return (1);
	var_name = ft_calloc(k + 1, sizeof(char));
	if (!var_name)
		return (0);
	ft_strlcpy(var_name, temp, k + 1);
	env_var = get_env_var(data, var_name + 1);
	if (!env_var)
		env_var = "";
	temp = ft_fndnrepl(*prompt, var_name, env_var);
	free(*prompt);
	*prompt = temp;
	free(var_name);
	return (0);
}

static void	do_check_variable(t_data *data, char **prompt, int for_argv)
{
	int	temp;

	temp = check_var_within_quotes(prompt, for_argv);
	if (temp == 2)
	{
		remove_invalid_var(prompt);
		check_variables(data, prompt, for_argv);
	}
	if (!temp)
	{
		if (set_env_var(data, prompt))
			return ;
		check_variables(data, prompt, for_argv);
	}
}

void	check_variables(t_data *data, char **prompt, int for_argv)
{
	if (*prompt)
	{
		if (for_argv && ft_strnstr(*prompt, "~/", ft_strlen(*prompt)))
		{
			set_home_var(data, prompt);
			check_variables(data, prompt, for_argv);
		}
		else if (ft_strchr(*prompt, '$') && \
		(ft_strchr(*prompt, '$') + 1)[0] != '?')
			do_check_variable(data, prompt, for_argv);
		else if (ft_strnstr(*prompt, "$?", ft_strlen(*prompt)))
		{
			set_exit_status(data, prompt);
			check_variables(data, prompt, for_argv);
		}
	}
}
