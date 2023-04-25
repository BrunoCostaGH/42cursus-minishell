/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:25:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/25 17:47:42 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

char	*get_env_var(char *prompt)
{
	char	*res;
	char	*var;
	char	**arguments;

	arguments = ft_split(data->prompt, ' ');
	var = ft_strtrim(arguments[0], "$");
	res = getenv(var);
	free_darr((void **)arguments);
	free(var);
	data->exit_status = 0;
	return (res);
}
