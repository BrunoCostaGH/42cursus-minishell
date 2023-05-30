/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:34:08 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/29 18:22:34 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go_to_text(char **argv, char flag)
{
	int	i;
	int	k;

	i = 1;
	while (argv[i])
	{
		k = 1;
		while (argv[i][0] == '-' && argv[i][k] == flag)
			k++;
		if (argv[i][0] != '-' || argv[i][k])
			break ;
		i++;
	}
	return (i);
}

void	echo(t_data *data, char **argv)
{
	int	i;

	i = go_to_text(argv, 'n');
	data->exit_status = 0;
	if (i > 1)
	{
		while (argv[i])
		{
			if (argv[i][ft_strlen(argv[i]) - 1] == '\n' || \
			argv[i][ft_strlen(argv[i]) - 1] == '\r')
				break ;
			printf("%s ", argv[i++]);
		}
		printf("\b");
	}
	else
	{
		i = 1;
		while (argv[i])
			printf("%s ", argv[i++]);
		printf("\b\n");
	}
}
