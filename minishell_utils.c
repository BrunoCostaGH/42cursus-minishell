/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:28:04 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/26 15:27:25 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(t_data *data, int id)
{
	if (data->argv.type[id] == PIPE)
		return ("|");
	else if (data->argv.type[id] == REDR_APPEND)
		return (">>");
	else if (data->argv.type[id] == REDR_OUTPUT)
		return (">");
	else if (data->argv.type[id] == REDR_DELIM)
		return ("<<");
	else if (data->argv.type[id] == REDR_INPUT)
		return ("<");
	else
		return (0);
}

int	check_identifier(t_data *data, char *command, char *arg)
{
	int		i;
	char	*temp;

	if (!arg || !*arg)
	{
		temp = ft_strjoin(command, ": ");
		handle_error(data, temp, 2);
		free(temp);
		return (1);
	}
	i = -1;
	while (arg[++i])
	{
		if (ft_isdigit(arg[0]) || !(ft_isalnum(arg[i]) || arg[i] == '_'))
		{
			temp = ft_strjoin(command, ": ");
			free(command);
			command = ft_strjoin(temp, arg);
			free(temp);
			handle_error(data, command, 2);
			free(command);
			return (1);
		}
	}
	return (0);
}

int	len_darr(void **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

void	free_darr(void **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = 0;
			i++;
		}
		free(arr);
		arr = 0;
	}
}
