/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:32:29 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/05 19:47:22 by bsilva-c         ###   ########.fr       */
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
	while (prompt && *prompt && (*prompt != ' ' || quote))
	{
		if ((*prompt == 34 || *prompt == 39) && quote)
			quote = FALSE;
		else if (*prompt == 34 || *prompt == 39)
			quote = TRUE;
		result[index_res][k++] = *prompt++;
		i++;
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
		while (*prompt && *prompt == ' ')
			prompt++;
		if (i && !ft_strncmp(prompt, "| ", 2))
		{
			data->argv.type[id + 1] = PIPE;
			prompt++;
		}
		else if (i && !ft_strncmp(prompt, "< ", 2))
		{
			data->argv.type[id + 1] = REDR_INPUT;
			prompt++;
		}
		else if (i && !ft_strncmp(prompt, "> ", 2))
		{
			data->argv.type[id + 1] = REDR_OUTPUT;
			prompt++;
		}
		else if (i && !ft_strncmp(prompt, ">> ", 3))
		{
			data->argv.type[id + 1] = REDR_APPEND;
			prompt += 2;
		}
		else if (i && !ft_strncmp(prompt, "<< ", 3))
		{
			data->argv.type[id + 1] = REDR_DELIM;
			prompt += 2;
		}
		if (data->argv.type[id + 1])
		{
			result[++id] = ft_calloc(string_count(prompt) + 1, sizeof(char *));
			if (!result[id])
				exit(0);
			i = 0;
			continue ;
		}
		if (*prompt && *prompt != ' ')
		{
			result[id][i] = ft_calloc(char_count(prompt) + 1, sizeof(char));
			if (!result[id][i])
				exit(0);
			prompt += special_treatment(prompt, result[id], i);
			i++;
		}
	}
}

void	set_argv(t_data *data)
{
	int			i;
	int			id;
	char		*temp;
	const char	*prompt;

	i = 0;
	id = 0;
	prompt = data->prompt;
	data->argv.args = ft_calloc(group_count(prompt) + 1, sizeof(char **));
	data->argv.args[0] = ft_calloc(string_count(prompt) + 1, sizeof(char *));
	data->argv.type = ft_calloc(group_count(prompt) + 1, sizeof(int));
	if (!data->argv.args || !data->argv.type)
		return ;
	set_result(data, prompt, data->argv.args);
	check_variables(data);
	while (data->argv.args && data->argv.args[id])
	{
		while (data->argv.args[id][i])
		{
			if (ft_strchr(data->argv.args[id][i], '\"'))
			{
				temp = ft_fndnrepl(data->argv.args[id][i], "\"", "");
				free(data->argv.args[id][i]);
				data->argv.args[id][i] = temp;
				continue ;
			}
			else if (ft_strchr(data->argv.args[id][i], '\''))
			{
				temp = ft_fndnrepl(data->argv.args[id][i], "\'", "");
				free(data->argv.args[id][i]);
				data->argv.args[id][i] = temp;
				continue ;
			}
			i++;
		}
		id++;
	}
}
