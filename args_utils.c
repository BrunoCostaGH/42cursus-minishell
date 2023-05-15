/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:51:41 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/11 20:04:15 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(const char *prompt)
{
	int	quotes;

	quotes = 0;
	while (*prompt++)
		if (*prompt == 34 || *prompt == 39)
			quotes++;
	return (quotes);
}

int	check_for_special_char(t_data *data, char *prompt, int id, int i)
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
	if (data->argv.type[id + 1] && data->argv.type[id + 1] % 2 == 0)
		return (2);
	else if (data->argv.type[id + 1])
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
		if ((*prompt == 34 || *prompt == 39) && quote)
			quote = FALSE;
		else if (*prompt == 34 || *prompt == 39)
			quote = TRUE;
		if (!ft_strncmp(prompt, "|", 1) || !ft_strncmp(prompt, ">>", 2) || \
			!ft_strncmp(prompt, ">", 1) || !ft_strncmp(prompt, "<<", 2) || \
			!ft_strncmp(prompt, "<", 1))
			break ;
		if (*prompt++ == ' ' && (!quote || !count_quotes(prompt)))
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
	while (prompt && *prompt && (*prompt != ' ' || \
			(quote && count_quotes(prompt))))
	{
		if ((*prompt == 34 || *prompt == 39) && quote)
			quote = FALSE;
		else if (*prompt == 34 || *prompt == 39)
			quote = TRUE;
		if (!ft_strncmp(prompt, "|", 1) || !ft_strncmp(prompt, ">>", 2) || \
			!ft_strncmp(prompt, ">", 1) || !ft_strncmp(prompt, "<<", 2) || \
			!ft_strncmp(prompt, "<", 1))
			break ;
		prompt++;
		i++;
	}
	return (i);
}
