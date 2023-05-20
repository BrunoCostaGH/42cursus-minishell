/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:32:12 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/20 15:42:28 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_data *data, char **argv)
{
	char	*path;

	if (argv[1])
	{
		handle_error(data, argv[0], 1);
		return ;
	}
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("Error");
		data->exit_status = errno;
		return ;
	}
	printf("%s\n", path);
	free(path);
	data->exit_status = 0;
}
