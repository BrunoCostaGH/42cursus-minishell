/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:10:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/02 20:43:45 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_data *data, char **argv)
{
	char	*path;

	if (argv[2])
	{
		write(2, "cd: too many arguments\n", 24);
		data->exit_status = 1;
		return ;
	}
	path = argv[1];
	if (!path)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror("Error");
		data->exit_status = errno;
		return ;
	}
	data->exit_status = 0;
}
