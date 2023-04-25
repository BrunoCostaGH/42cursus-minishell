/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:15 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/25 20:47:58 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*init_struct(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->interactive = TRUE;
	data->exit_status = 0;
	data->prompt = NULL;
	data->envp = envp;
	return (data);
}
