/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:32:29 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/22 17:04:27 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return numbers of split strings
static int	string_count(char const *prompt)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)prompt;
	while (*str)
	{
		if (*str++ == ' ')
			i++;
	}
	return (++i);
}

//return numbers of current string characters
static int	char_count(char const *prompt)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)prompt;
	if (*str == 34 || *str == 39)
	{
		str++;
		while (*str != 34 && *str != 39 && *str)
		{
			str++;
			i++;
		}
	}
	else
	{
		while (*str != ' ' && *str)
		{
			str++;
			i++;
		}
	}
	return (i);
}

void	set_result(const char *prompt, char **result)
{
	int	i;
	int	k;

	i = -1;
	while (*prompt)
	{
		k = 0;
		while (*prompt == ' ' && *prompt)
			prompt++;
		if (*prompt != ' ' && *prompt)
		{
			result[++i] = ft_calloc(char_count(prompt) + 1, sizeof(char));
			if (!result[i])
				exit(0);
			if (*prompt == 34 || *prompt == 39)
			{
				while (*++prompt != 34 && *prompt != 39 && *prompt)
					result[i][k++] = *prompt;
				prompt++;
			}
			else
				while (*prompt != ' ' && *prompt)
					result[i][k++] = *prompt++;
		}
	}
}

char	**set_argv(const char *prompt)
{
	char	**result;

	result = ft_calloc(string_count(prompt) + 1, sizeof(char *));
	if (!result)
		return (0);
	set_result(prompt, result);
	return (result);
}
