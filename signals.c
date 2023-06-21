/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:17:40 by tabreia-          #+#    #+#             */
/*   Updated: 2023/06/21 15:07:49 by bsilva-c         ###   ########.fr       */
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
		if (sig == SIGINT)
		{
			printf("\b\b  \b\b");
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (sig == SIGQUIT)
		{
			printf("\b\b  \b\b");
			rl_redisplay();
		}
	}
	if (!(static_data->interactive))
		if (sig == SIGINT)
			write(1, &"\n", 1);
	if (sig == SIGINT)
		static_data->exit_status = 130;
}

void	handle(int sig)
{
	execute_sig_action(sig, 0);
}

void	set_handle_struct(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
