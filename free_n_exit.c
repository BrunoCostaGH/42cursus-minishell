/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:31:46 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/05 19:19:45 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argv_clear(t_data *data)
{
	int	id;

	id = 0;
	while (data->argv.args && data->argv.args[id])
	{
		free_darr((void **)data->argv.args[id]);
		data->argv.args[id] = 0;
		id++;
	}
	free(data->argv.type);
	data->argv.args = 0;
	data->argv.type = 0;
}

void	shell_exit(t_data *data)
{
	rl_clear_history();
	if (data->prompt)
		free(data->prompt);
	if (data->argv.args)
		argv_clear(data);
	if (data->envp)
		free_darr((void **)data->envp);
	free(data);
	exit(0);
}
