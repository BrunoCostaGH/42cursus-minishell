/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:10:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/21 20:10:17 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char *prompt)
{
	char	*path;
	char	**prompt_arr;


	prompt_arr = ft_split(prompt, ' ');
	if (!prompt_arr[1])
		path = getenv("HOME");
	else
		path = ft_strtrim(prompt, "cd ");
	chdir(path);
}
