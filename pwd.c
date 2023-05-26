/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:32:12 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/21 15:30:57 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("Error");
		data->exit_status = 1;
		return ;
	}
	printf("%s\n", path);
	free(path);
	data->exit_status = 0;
}
