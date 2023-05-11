/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:32:29 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/11 18:22:19 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_special_char(t_data *data, char *prompt, int id, int i)
{
	if (i && !ft_strncmp(prompt, "|", 1))
		data->argv.type[id + 1] = PIPE;
	else if (i && !ft_strncmp(prompt, ">>", 2))
		data->argv.type[id + 1] = REDR_APPEND;
	else if (i && !ft_strncmp(prompt, ">", 1))
		data->argv.type[id + 1] = REDR_OUTPUT;
	else if (i && !ft_strncmp(prompt, "<<", 2))
		data->argv.type[id + 1] = REDR_DELIM;
	else if (i && !ft_strncmp(prompt, "<", 1))
		data->argv.type[id + 1] = REDR_INPUT;
	if (data->argv.type[id + 1] % 2 == 0)
		return (2);
	else if (data->argv.type[id + 1])
		return (1);
	return (0);
}

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
		if (!ft_strncmp(prompt, "|", 1) || !ft_strncmp(prompt, ">>", 2) || \
			!ft_strncmp(prompt, ">", 1) || !ft_strncmp(prompt, "<<", 2) || \
			!ft_strncmp(prompt, "<", 1))
			break ;
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
		while (*prompt && (*prompt == ' ' || *prompt == '\t'))
			prompt++;
		prompt += check_for_special_char(data, (char *)prompt, id, i);
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
