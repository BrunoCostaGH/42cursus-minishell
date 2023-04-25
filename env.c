/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:25:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/25 14:30:24 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *prompt)
{
	char	*res;
	char	*var;
	char	**arguments;

	arguments = ft_split(prompt, ' ');
	var = ft_strtrim(arguments[0], "$");
	res = getenv(var);
	free_darr(arguments);
	free(var);
	return (res);
}
