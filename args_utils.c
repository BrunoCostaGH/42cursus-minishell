/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:51:41 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/05 15:34:03 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	group_count(const char *prompt)
{
	int	i;

	i = 0;
	while (prompt && *prompt)
	{
		if (!ft_strncmp(prompt, " | ", 3) || !ft_strncmp(prompt, " < ", 3) || \
			!ft_strncmp(prompt, " > ", 3) || !ft_strncmp(prompt, " >> ", 4) || \
			!ft_strncmp(prompt, " << ", 4))
			i++;
		prompt++;
	}
	return (++i);
}

//return numbers of split strings
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
		if (*prompt++ == ' ' && !quote)
			i++;
	}
	return (++i);
}

//return numbers of current string characters
int	char_count(const char *prompt)
{
	int	i;
	int	quote;

	i = 0;
	quote = FALSE;
	while (prompt && *prompt && (*prompt != ' ' || quote))
	{
		if ((*prompt == 34 || *prompt == 39) && quote)
			quote = FALSE;
		else if (*prompt == 34 || *prompt == 39)
			quote = TRUE;
		prompt++;
		i++;
	}
	return (i);
}
