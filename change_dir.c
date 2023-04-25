/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:10:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/25 17:08:42 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(t_data *data)
{
	char	*path;
	char	**prompt_arr;

	prompt_arr = ft_split(data->prompt, ' ');
	path = prompt_arr[1];
	if (!path)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		perror("Error");
		data->exit_status = errno;
		free_darr((void **)prompt_arr);
		return ;
	}
	free_darr((void **)prompt_arr);
	data->exit_status = 0;
}
