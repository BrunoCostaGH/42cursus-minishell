/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:03:13 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/22 18:23:27 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	char	*temp;

	while (1)
	{
		prompt = readline("\x1B[1;32m(Minishell)$ \x1B[0m");
		if (!ft_strncmp(prompt, "exit", ft_strlen("exit")))
			shell_exit(prompt);
		if (!ft_strncmp(prompt, "cd", ft_strlen("cd")))
			change_dir(prompt);
		if (!ft_strncmp(prompt, "pwd", ft_strlen("pwd")))
			pwd();
		if (!ft_strncmp(prompt, "$", ft_strlen("$")))
		{
			temp = ft_strtrim(prompt, "$");
			getenv(temp);
			free(temp);
		}
		if (prompt[0] != '\0')
			add_history(prompt);
	}
}
