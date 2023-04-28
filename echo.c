/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:34:08 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/27 17:02:46 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	int	i;

	if (data->argv[1])
	{
		if (!ft_strncmp(data->argv[1], "-n", 3) && data->argv[2])
		{
			i = 2;
			while (data->argv[i])
			{
				if (data->argv[i][ft_strlen(data->argv[i]) - 1] == '\n' || \
				data->argv[i][ft_strlen(data->argv[i]) - 1] == '\r')
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
	}
	data->exit_status = 0;
}