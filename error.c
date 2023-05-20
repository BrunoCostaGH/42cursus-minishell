/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:32:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/20 14:24:19 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * error: 0: not enough arguments
 * error: 1: too many arguments
 * error: 2: not a valid identifier
 * error: 3: numeric argument required
 * */
int	handle_error(t_data *data, char *command, int error)
{
	if (error == 0)
	{
		write(2, command, ft_strlen(command));
		write(2, ": not enough arguments\n", 23);
		data->exit_status = 1;
	}
	else if (error == 1)
	{
		write(2, command, ft_strlen(command));
		write(2, ": too many arguments\n", 21);
		data->exit_status = 1;
	}
	else if (error == 2)
	{
		write(2, command, ft_strlen(command));
		write(2, ": not a valid identifier\n", 25);
		data->exit_status = 1;
	}
	else if (error == 3)
	{
		write(2, command, ft_strlen(command));
		write(2, ": numeric argument required\n", 28);
		data->exit_status = 2;
	}
	return (data->exit_status);
}
