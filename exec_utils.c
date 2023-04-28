/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:32:29 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/28 21:01:10 by bsilva-c         ###   ########.fr       */
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
		i++;
		prompt++;
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
	while (prompt[i] && (prompt[i] != ' ' || quote))
	{
		if ((prompt[i] == 34 || prompt[i] == 39) && quote)
			quote = FALSE;
		else if (*prompt == 34 || *prompt == 39)
			quote = TRUE;
		result[index_res][k++] = prompt[i++];
	}
	return (++i);
}

void	set_result(const char *prompt, char **result)
{
	int	i;

	i = -1;
	while (*prompt)
	{
		while (*prompt == ' ' && *prompt)
			prompt++;
		if (*prompt != ' ' && *prompt)
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
	while (data->argv[i])
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
