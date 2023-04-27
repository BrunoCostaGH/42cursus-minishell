/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:34:08 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/27 14:15:35 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	int	i;

	if (data->argv[1][0] == '-' && data->argv[1][1] == 'n' && !data->argv[1][2])
	{
		i = 2;
		while (data->argv[i])
		{
			if (data->argv[i][ft_strlen(data->argv[i]) - 1] == '\n')
				break ;
			if (data->argv[i][ft_strlen(data->argv[i]) - 1] == '\r')
				break ;
			ft_printf("%s ", data->argv[i++]);
		}
		ft_printf("\b");
	}
	else
	{
		i = 1;
		while (data->argv[i])
			ft_printf("%s ", data->argv[i++]);
		ft_printf("\b\n");
	}
	data->exit_status = 0;
}
