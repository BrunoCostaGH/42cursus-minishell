/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:39:02 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/23 14:53:43 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	remove_invalid_var(char **prompt)
{
	int		i;
	char	*temp;
	char	*temp_res;

	i = 0;
	while ((*prompt)[i])
	{
		if ((*prompt)[i] == '$')
		{
			if ((*prompt)[++i] && ft_isdigit((*prompt)[i]))
			{
				temp = ft_chrjoin('$', (*prompt)[i]);
				temp_res = ft_fndnrepl((*prompt), temp, "");
				free(temp);
				free((*prompt));
				(*prompt) = temp_res;
			}
			else if ((*prompt)[i] && ((*prompt)[i] == '\'' || \
			(*prompt)[i] == '\"'))
			{
				temp_res = ft_fndnrepl((*prompt), "$", "");
				free((*prompt));
				(*prompt) = temp_res;
			}
			else if ((ft_isalnum((*prompt)[i]) || (*prompt)[i] == '_'))
				break ;
		}
		i++;
	}
}
