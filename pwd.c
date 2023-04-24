/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:32:12 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/24 15:14:36 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (path == NULL)
		perror("Error");
	ft_printf("%s\n", path);
	free(path);
}
