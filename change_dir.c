/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:10:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/01 15:35:59 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_data *data, char **argv)
{
	char	*path;

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
