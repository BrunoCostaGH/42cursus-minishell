/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:39:02 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/24 19:15:22 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_within_quotes(char **prompt)
{
	int	i;
	int	quote;

	i = 0;
	quote = FALSE;
	while (*prompt && (*prompt)[i])
	{
		if (handle_quote(*prompt + i, &i, &quote))
			continue ;
		if (quote == 39 && (*prompt)[i] == '$')
			return (TRUE);
		else if ((*prompt)[i] == '$')
		{
			if ((*prompt)[++i] && (ft_isdigit((*prompt)[i]) || \
			(*prompt)[i] == '\'' || (*prompt)[i] == '\"' ))
				return (2);
			else if (!(*prompt)[i] || \
			(ft_isalnum((*prompt)[i]) || (*prompt)[i] == '_'))
				break ;
		}
		i++;
	}
	return (FALSE);
}

char	*find_variable(const char *big, const char *little, size_t len)
{
	int	redir;

	redir = 0;
	while ((size_t)ft_strlen(little) <= len--)
	{
		if (redir && *big == '$')
		{
			big++;
			continue ;
		}
		if (ft_strncmp(big, little, ft_strlen(little)) == 0)
			return ((char *)big);
		if (ft_strncmp(big, "<<", 2) == 0)
			redir = 1;
		if (redir && *big != 60 && *big != 32 && *big != 9)
			redir = 0;
		big++;
	}
	return (0);
}

static int	check_if_invalid_var(char **prompt, int *i)
{
	char	*temp;
	char	*temp_res;

	if ((*prompt)[*++i] && ft_isdigit((*prompt)[*i]))
	{
		temp = ft_chrjoin('$', (*prompt)[*i]);
		temp_res = ft_fndnrepl((*prompt), temp, "");
		free(temp);
		free((*prompt));
		(*prompt) = temp_res;
	}
	else if ((*prompt)[*i] && ((*prompt)[*i] == '\'' || \
			(*prompt)[*i] == '\"'))
	{
		temp_res = ft_fndnrepl((*prompt), "$", "");
		free((*prompt));
		(*prompt) = temp_res;
	}
	else if ((ft_isalnum((*prompt)[*i]) || (*prompt)[*i] == '_'))
		return (1);
	return (0);
}

void	remove_invalid_var(char **prompt)
{
	int		i;

	i = 0;
	while ((*prompt)[i])
	{
		if ((*prompt)[i] == '$')
			if (check_if_invalid_var(prompt, &i) == 1)
				break ;
		i++;
	}
}
