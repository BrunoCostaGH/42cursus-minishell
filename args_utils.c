/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:51:41 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/16 17:28:27 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	regroup_argv(t_data *data)
{
	int		i;
	int		k;
	int		j;
	char	**temp;

	i = 0;
	while (data->argv.args[i + 1])
	{
		k = 0;
		j = 0;
		if (data->argv.type[i] == 0 && data->argv.args[i + 1][0])
		{
			temp = ft_calloc((darr_len((void **)data->argv.args[i]) \
			+ darr_len((void **)data->argv.args[i + 1]) + 1), (sizeof(char *)));
			if (!temp)
				return ;
			while (data->argv.args[i][k])
			{
				temp[k] = ft_strdup(data->argv.args[i][k]);
				k++;
			}
			while (data->argv.args[i + 1][j])
			{
				temp[k] = ft_strdup(data->argv.args[i + 1][j++]);
				k++;
			}
			free_darr((void **)data->argv.args[i]);
			data->argv.args[i] = temp;
			free_darr((void **)data->argv.args[i + 1]);
			k = i + 1;
			while (data->argv.args[++k])
				data->argv.args[k - 1] = data->argv.args[k];
			data->argv.args[k - 1] = 0;
			k = i;
			while (data->argv.type[++k])
				data->argv.type[k - 1] = data->argv.type[k];
			data->argv.type[k - 1] = 0;
			continue ;
		}
		i++;
	}
}

int	check_for_special_char(t_data *data, const char *prompt, int *i, int id)
{
	if (i && !ft_strncmp(prompt, "|", 1))
		data->argv.type[id] = PIPE;
	else if (i && !ft_strncmp(prompt, ">>", 2))
		data->argv.type[id] = REDR_APPEND;
	else if (i && !ft_strncmp(prompt, ">", 1))
		data->argv.type[id] = REDR_OUTPUT;
	else if (i && !ft_strncmp(prompt, "<<", 2))
		data->argv.type[id] = REDR_DELIM;
	else if (i && !ft_strncmp(prompt, "<", 1))
		data->argv.type[id] = REDR_INPUT;
	if (data->argv.type[id] && data->argv.type[id] % 2 == 0)
	{
		*i = 0;
		return (2);
	}
	else if (data->argv.type[id])
	{
		*i = 0;
		return (1);
	}
	return (0);
}

int	count_group(const char *prompt)
{
	int	i;

	i = 0;
	while (prompt && *prompt)
	{
		if (!ft_strncmp(prompt, ">>", 2) || !ft_strncmp(prompt, "<<", 2))
		{
			i++;
			prompt += 2;
			continue ;
		}
		else if (!ft_strncmp(prompt, "|", 1) || !ft_strncmp(prompt, ">", 1) || \
			!ft_strncmp(prompt, "<", 1))
			i++;
		prompt++;
	}
	return (++i);
}

int	count_string(const char *prompt)
{
	int	i;
	int	quote;

	i = 0;
	quote = FALSE;
	while (prompt && *prompt)
	{
		if (handle_quote(prompt, NULL, &quote))
		{
			prompt++;
			continue ;
		}
		if ((!ft_strncmp(prompt, "|", 1) || !ft_strncmp(prompt, ">>", 2) || \
			!ft_strncmp(prompt, ">", 1) || !ft_strncmp(prompt, "<<", 2) || \
			!ft_strncmp(prompt, "<", 1)) && !quote)
			break ;
		if (*prompt++ == ' ' && !quote)
			i++;
	}
	return (++i);
}

int	count_char(const char *prompt)
{
	int	i;
	int	quote;

	i = 0;
	quote = FALSE;
	while (prompt && *prompt && (*prompt != ' ' || quote))
	{
		if (handle_quote(prompt, NULL, &quote))
		{
			prompt++;
			continue ;
		}
		if ((!ft_strncmp(prompt, "|", 1) || !ft_strncmp(prompt, ">>", 2) || \
			!ft_strncmp(prompt, ">", 1) || !ft_strncmp(prompt, "<<", 2) || \
			!ft_strncmp(prompt, "<", 1)) && !quote)
			break ;
		prompt++;
		i++;
	}
	return (i);
}
