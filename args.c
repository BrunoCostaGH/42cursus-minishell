/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:32:29 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/28 23:04:54 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	special_treatment(const char *prompt, char **result, int index_res)
{
	int	i;
	int	k;
	int	quote;

	i = 0;
	k = 0;
	quote = FALSE;
	while (prompt[i] && (prompt[i] != ' ' || quote))
	{
		if (handle_quote(prompt + i, &i, &quote))
			continue ;
		if ((!ft_strncmp(prompt + i, "|", 1) || \
		!ft_strncmp(prompt + i, ">>", 2) || !ft_strncmp(prompt + i, ">", 1) || \
		!ft_strncmp(prompt + i, "<<", 2) || !ft_strncmp(prompt + i, "<", 1)) \
		&& !quote)
			break ;
		result[index_res][k++] = prompt[i++];
	}
	return (i);
}

static void	set_result(t_data *data, const char *prompt, char ***result)
{
	int	i;
	int	id;

	i = 0;
	id = 0;
	while (prompt && *prompt)
	{
		while (*prompt && (*prompt == ' ' || *prompt == '\t'))
			prompt++;
		prompt += check_for_special_char(data, prompt, &i, id);
		if (data->argv.type[id])
		{
			result[++id] = ft_calloc(string_count(prompt) + 1, sizeof(char *));
			if (!result[id])
				return ;
			continue ;
		}
		if (*prompt && *prompt != ' ')
		{
			result[id][i] = ft_calloc(char_count(prompt) + 1, sizeof(char));
			if (!result[id][i])
				return ;
			prompt += special_treatment(prompt, result[id], i++);
		}
	}
}

void	set_argv(t_data *data)
{
	int			id;
	const char	*prompt;

	id = 0;
	check_variables(data);
	prompt = data->prompt;
	data->argv.args = ft_calloc(group_count(prompt) + 1, sizeof(char **));
	data->argv.args[0] = ft_calloc(string_count(prompt) + 1, sizeof(char *));
	data->argv.type = ft_calloc(group_count(prompt) + 2, sizeof(int));
	if (!data->argv.args || !data->argv.type)
		return ;
	set_result(data, prompt, data->argv.args);
	init_pipe_fd(data);
	while (data->argv.type[id++])
	{
		if ((!data->argv.args[id] || !data->argv.args[id][0]) || \
		(data->argv.type[id - 1] == PIPE && !data->argv.args[id - 1][0]))
		{
			if (data->argv.type[id])
				handle_error(data, get_token(data, id), 5);
			else
				handle_error(data, get_token(data, id - 1), 5);
			return ;
		}
	}
}
