/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:32:12 by tabreia-          #+#    #+#             */
/*   Updated: 2023/10/05 19:24:47 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_data *data)
{
	char	*path;

	path = getcwd(0, 0);
	data->exit_status = 0;
	if (!path)
	{
		handle_error(data, 0, 0);
		return ;
	}
	ft_printf("%s\n", path);
	free(path);
}
