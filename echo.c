/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:34:08 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/02 14:35:48 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data, char **argv)
{
	int	i;

	if (argv[1])
	{
		if ((!ft_strncmp(argv[1], "-n", 3) || !ft_strncmp(argv[1], "-n ", 3)))
		{
			i = 2;
			while (argv[i])
			{
				if (argv[i][ft_strlen(argv[i]) - 1] == '\n' || \
				argv[i][ft_strlen(argv[i]) - 1] == '\r')
					break ;
				ft_printf("%s ", argv[i++]);
			}
			ft_printf("\b");
		}
		else
		{
			i = 1;
			while (argv[i])
				ft_printf("%s ", argv[i++]);
			ft_printf("\b\n");
		}
	}
	data->exit_status = 0;
}
