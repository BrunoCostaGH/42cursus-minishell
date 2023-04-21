/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:03:13 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/21 20:24:12 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;

	while (1)
	{
		prompt = 0;
		ft_printf("\x1B[1;32m(Minishell)$ \x1B[0m");
		prompt = readline(prompt);
		if (!ft_strncmp(prompt, "exit", ft_strlen("exit")))
			shell_exit();
		if (!ft_strncmp(prompt, "cd", ft_strlen("cd")))
			change_dir(prompt);
		if (!ft_strncmp(prompt, "pwd", ft_strlen("pwd")))
			pwd();
		if (!ft_strncmp(prompt, "$", ft_strlen("$")))
			getenv(ft_strtrim(prompt, "$"));
		if (prompt[0] == '\0')
			ft_printf("\n");
		else
			add_history(prompt);
	}
}
