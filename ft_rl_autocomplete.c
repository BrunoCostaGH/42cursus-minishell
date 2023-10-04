/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocomplete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:26:20 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/04 15:47:15 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

/*
 * TODO fix cursor not returning to prompt line after printing
 * TODO add autocomplete to prompt
 * TODO iterate through autocomplete with tab
 */
char	*ft_rl_autocomplete(char *string)
{
	int				index;
	DIR				*dir;
	struct dirent	*dir_info;

	index = 0;
	dir = opendir(getenv("PWD"));
	dir_info = readdir(dir);
	while (dir_info)
	{
		if (ft_strncmp(string, dir_info->d_name, ft_strlen(string)) == 0)
		{
			if (index++ == 0)
				ft_printf("\n");
			ft_printf("%s\t", dir_info->d_name);
		}
		dir_info = readdir(dir);
	}
	return (0);
}
