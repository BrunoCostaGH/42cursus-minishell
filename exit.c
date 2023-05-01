/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:31:46 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/01 16:44:59 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exit(t_data *data)
{
	rl_clear_history();
	if (data->argv)
		free_darr((void **)data->argv);
	free_darr((void **)data->envp);
	free(data->prompt);
	free(data);
	exit(0);
}
