/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:51:41 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/21 15:06:19 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote(const char *prompt, int *index, int *quote)
{
	if (*prompt == *quote)
		*quote = FALSE;
	else if ((*prompt == 34 || *prompt == 39) && \
		ft_strchr(prompt + 1, *prompt) && !*quote)
		*quote = (int)*prompt;
	else
		return (0);
	if (index)
		*index = *index + 1;
	return (1);
}

int	check_for_special_char(t_data *data, const char *prompt, int id, int i)
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
		return (2);
	else if (data->argv.type[id])
		return (1);
	return (0);
}

int	group_count(const char *prompt)
{
	int	i;

	i = 0;
	while (prompt && *prompt)
	{
		if (!ft_strncmp(prompt, "|", 1) || !ft_strncmp(prompt, ">>", 2) || \
			!ft_strncmp(prompt, ">", 1) || !ft_strncmp(prompt, "<<", 2) || \
			!ft_strncmp(prompt, "<", 1))
			i++;
		prompt++;
	}
	return (++i);
}

int	string_count(const char *prompt)
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

int	char_count(const char *prompt)
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
