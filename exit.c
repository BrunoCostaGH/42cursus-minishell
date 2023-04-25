/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:31:46 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/25 14:47:25 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exit(t_data *data)
{
	free(data->prompt);
	rl_clear_history();
	free(data);
	exit(0);
}
