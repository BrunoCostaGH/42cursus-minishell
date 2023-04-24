/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:10:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/24 15:06:58 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char *prompt)
{
	int		i;
	char	*path;
	char	**prompt_arr;

	i = 0;
	prompt_arr = ft_split(prompt, ' ');
	if (!prompt_arr[1])
	{
		path = getenv("HOME");
		if (chdir(path) == -1)
			perror("Error");
	}
	else
	{
		path = prompt_arr[1];
		if (chdir(path) == -1)
			perror("Error");
	}
	while (prompt_arr[i])
	{
		free(prompt_arr[i]);
		i++;
	}
	free(prompt_arr);
}
