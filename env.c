/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:25:14 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/25 15:40:26 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_data *data)
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
