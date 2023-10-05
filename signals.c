/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:17:40 by tabreia-          #+#    #+#             */
/*   Updated: 2023/10/05 19:24:47 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_sig_action(int sig, void *data)
{
	static t_data	*static_data;

	if (!static_data && data)
		static_data = (t_data *)data;
	if (static_data && static_data->interactive)
	{
		if (sig == 2)
			ft_printf("\n");
	}
	if (sig == 2)
		static_data->exit_status = 130;
}

static void	handle(int sig)
{
	execute_sig_action(sig, 0);
}

void	set_handle_struct(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(2, &sa, 0);
	sigaction(3, &sa, 0);
}
