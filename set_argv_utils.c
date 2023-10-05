/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_argv_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:51:41 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/05 19:24:47 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (handle_quote(prompt, 0, &quote))
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
		if (handle_quote(prompt, 0, &quote))
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
