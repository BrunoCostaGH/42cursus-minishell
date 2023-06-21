/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:16:07 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/21 20:11:20 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var_within_quotes(char **prompt)
{
	int	i;
	int	quote;

	i = 0;
	quote = FALSE;
	while (*prompt && (*prompt)[i])
	{
		if (handle_quote(*prompt + i, &i, &quote))
			continue ;
		if (quote == 39 && (*prompt)[i] == '$')
			return (TRUE);
		else if ((*prompt)[i] == '$')
		{
			if ((*prompt)[++i] && (ft_isdigit((*prompt)[i]) || \
			(*prompt)[i] == '\'' || (*prompt)[i] == '\"' ))
				return (2);
			else if ((ft_isalnum((*prompt)[i]) || (*prompt)[i] == '_'))
				break ;
		}
		i++;
	}
	return (FALSE);
}

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

	temp = ft_strnstr(*prompt, "$", ft_strlen(*prompt));
	k = 0;
	while (temp[++k])
		if (!(ft_isalnum(temp[k]) || temp[k] == '_'))
			break ;
	if (k == 1)
		return (1);
	var_name = ft_calloc(k + 1, sizeof(char));
	if (!var_name)
		return (0);
	ft_strlcpy(var_name, temp, k + 1);
	env_var = get_env_var(data, var_name + 1);
	if (!env_var)
		env_var = "";
	printf("prompt: %s\nvar_name: %s\nenv_var: %s\n", *prompt, var_name, env_var);
	temp = ft_fndnrepl(*prompt, var_name, env_var);
	free(*prompt);
	*prompt = temp;
	free(var_name);
	return (0);
}

void	check_variables(t_data *data, char **prompt)
{
	int	temp;

	if (*prompt)
	{
		if (ft_strnstr(*prompt, "~/", ft_strlen(*prompt)))
		{
			set_home_var(data, prompt);
			check_variables(data, prompt);
		}
		else if (ft_strchr(*prompt, '$') && \
		(ft_strchr(*prompt, '$') + 1)[0] != '?')
		{
			temp = check_var_within_quotes(prompt);
			if (temp == 2)
			{
				remove_invalid_var(prompt);
				check_variables(data, prompt);
			}
			else if (!temp)
			{
				if (set_env_var(data, prompt))
					return ;
				check_variables(data, prompt);
			}
		}
		else if (ft_strnstr(*prompt, "$?", ft_strlen(*prompt)))
		{
			set_exit_status(data, prompt);
			check_variables(data, prompt);
		}
	}
}
