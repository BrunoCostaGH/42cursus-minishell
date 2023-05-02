/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:32:29 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/02 14:09:52 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return numbers of split strings
static int	string_count(const char *prompt)
{
	int		i;
	int		quote;

	i = 0;
	quote = FALSE;
	while (*prompt)
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
static int	char_count(const char *prompt)
{
	int		i;
	int		quote;

	i = 0;
	quote = FALSE;
	while (*prompt && (*prompt != ' ' || quote))
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

static int	special_treatment(const char *prompt, char **result, int index_res)
{
	int	i;
	int	k;
	int	quote;

	i = 0;
	k = 0;
	quote = FALSE;
	while (*prompt && (*prompt != ' ' || quote))
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

void	set_result(const char *prompt, char **result)
{
	int	i;

	i = -1;
	while (prompt && *prompt)
	{
		while (*prompt && *prompt == ' ')
			prompt++;
		if (*prompt && *prompt != ' ')
		{
			result[++i] = ft_calloc(char_count(prompt) + 1, sizeof(char));
			if (!result[i])
				exit(0);
			prompt += special_treatment(prompt, result, i);
		}
	}
}

void	set_argv(t_data *data)
{
	int			i;
	char		*temp;
	const char	*prompt;

	i = 0;
	prompt = data->prompt;
	data->argv = ft_calloc(string_count(prompt) + 1, sizeof(char *));
	if (!data->argv)
		return ;
	set_result(prompt, data->argv);
	check_variables(data);
	while (data->argv && data->argv[i])
	{
		if (ft_strchr(data->argv[i], '\"'))
		{
			temp = ft_fndnrepl(data->argv[i], "\"", "");
			free(data->argv[i]);
			data->argv[i] = temp;
			continue ;
		}
		else if (ft_strchr(data->argv[i], '\''))
		{
			temp = ft_fndnrepl(data->argv[i], "\'", "");
			free(data->argv[i]);
			data->argv[i] = temp;
			continue ;
		}
		i++;
	}
}
