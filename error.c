/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:32:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/29 18:54:18 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error2(t_data *data, char *command, int error)
{
	if (error == 4)
	{
		write(2, command, ft_strlen(command));
		write(2, ": numeric argument required\n", 28);
		data->exit_status = 2;
	}
	else if (error == 5)
	{
		write(2, &"Error: syntax error near unexpected token `", 43);
		write(2, command, ft_strlen(command));
		write(2, &"'\n", 2);
		clear_argv(data);
		data->exit_status = 2;
	}
	return (data->exit_status);
}

/*
 * error: 0: stderr
 * error: 1: not enough arguments
 * error: 2: too many arguments
 * error: 3: not a valid identifier
 * error: 4: numeric argument required
 * error: 5: syntax error near unexpected token
 * */
int	handle_error(t_data *data, char *command, int error)
{
	if (error == 0)
	{
		perror("Error");
		data->exit_status = 1;
	}
	else if (error == 1)
	{
		write(2, command, ft_strlen(command));
		write(2, ": not enough arguments\n", 23);
		data->exit_status = 1;
	}
	else if (error == 2)
	{
		write(2, command, ft_strlen(command));
		write(2, ": too many arguments\n", 21);
		data->exit_status = 1;
	}
	else if (error == 3)
	{
		write(2, command, ft_strlen(command));
		write(2, ": not a valid identifier\n", 25);
		data->exit_status = 1;
	}
	return (handle_error2(data, command, error));
}
