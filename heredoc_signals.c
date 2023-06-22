/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:01:18 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/22 20:05:19 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_sig_int(int sig, void *data)
{
	static t_data	*static_data;

	if (!static_data && data)
		static_data = (t_data *)data;
	if (static_data)
	{
		if (sig == SIGINT)
		{
			static_data->exit_status = 130;
			exit_shell(static_data, 0);
		}
	}
}

static void	handle(int sig)
{
	execute_sig_int(sig, 0);
}

void	set_heredoc_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	signal(SIGINT, SIG_DFL);
	sigaction(SIGINT, &sa, NULL);
}
