/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:28:04 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/21 18:47:05 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier(t_data *data, char *command, char *arg)
{
	int		index;
	char	*temp;

	if (!arg || !*arg)
	{
		temp = ft_strjoin(command, ": ");
		handle_error(data, temp, 2);
		free(temp);
		return (1);
	}
	index = -1;
	while (arg[++index])
	{
		if (!(ft_isalnum(arg[index]) || arg[index] == '_'))
		{
			temp = ft_strjoin(command, ": ");
			free(command);
			command = temp;
			temp = ft_strjoin(command, arg);
			handle_error(data, temp, 2);
			free(temp);
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
