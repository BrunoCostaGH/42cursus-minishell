/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:33:43 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/04 20:38:54 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

/*
 * DESCRIPTION
 * Delete text from input from start to end, inclusive.
 */
void	m_rl_delete_text(void *p_data, int start, int end)
{
	static t_readline	*rl_data;
	char				*before_str;
	char				*after_str;

	if (!rl_data || p_data)
	{
		if (!rl_data && p_data)
			rl_data = (t_readline *)p_data;
		return ;
	}
	else if (!rl_data->input)
		return ;
	before_str = ft_calloc(ft_strlen(rl_data->input) - (end - start + 1) + 1, \
		sizeof(char));
	ft_strlcpy(before_str, rl_data->input, start + 1);
	after_str = ft_strdup((rl_data->input + end + 1));
	free(rl_data->input);
	rl_data->input = ft_strjoin(before_str, after_str);
	if (before_str)
		free(before_str);
	if (after_str)
		free(after_str);
	if (ft_strlen(rl_data->input) == 0)
	{
		free(rl_data->input);
		rl_data->input = 0;
	}
}

/*
 * RETURN VALUE
 * Returns a memory allocated string with the updated string
 */
int	ft_rl_delete_text(int start, int end)
{
	m_rl_delete_text(0, start, end);
	return (0);
}

void	m_rl_insert_text(void *p_data, char *text)
{
	static t_readline	*rl_data;
	char				*before_str;
	char				*after_str;

	if (!rl_data || p_data)
	{
		if (!rl_data && p_data)
			rl_data = (t_readline *)p_data;
		return ;
	}
	else if (!text)
		return ;
	if (!rl_data->input)
		rl_data->input = ft_calloc(1, sizeof(char));
	before_str = ft_calloc(ft_strlen(rl_data->input) + ft_strlen(text) + 1, \
		sizeof(char));
	ft_strlcpy(before_str, rl_data->input, rl_data->cursor_offset + 1);
	after_str = ft_strdup(rl_data->input + rl_data->cursor_offset);
	free(rl_data->input);
	rl_data->input = ft_strjoin(before_str, text);
	if (before_str)
		free(before_str);
	before_str = ft_strjoin(rl_data->input, after_str);
	if (rl_data->input)
		free(rl_data->input);
	if (after_str)
		free(after_str);
	rl_data->input = before_str;
}

/*
 * RETURN VALUE
 * Returns a memory allocated string with the updated string
 */
int	ft_rl_insert_text(char *text)
{
	m_rl_insert_text(0, text);
	return (0);
}
