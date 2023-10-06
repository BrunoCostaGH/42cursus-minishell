/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocomplete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:26:20 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/06 17:59:38 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	*ft_rl_input_autocomplete(char *string)
{
	char			*_return;
	char			buf[256];
	DIR				*dir;
	struct dirent	*dir_info;

	getcwd(buf, 256);
	dir = opendir(buf);
	dir_info = readdir(dir);
	while (dir_info)
	{
		if (string && ft_strncmp(string, dir_info->d_name, \
			ft_strlen(string)) == 0)
		{
			_return = ft_strdup(dir_info->d_name);
			closedir(dir);
			return (_return);
		}
		dir_info = readdir(dir);
	}
	closedir(dir);
	return (0);
}

int	ft_rl_autocomplete(char *string)
{
	int				num_matches;
	char			buf[256];
	DIR				*dir;
	struct dirent	*dir_info;

	num_matches = 0;
	getcwd(buf, 256);
	dir = opendir(buf);
	dir_info = readdir(dir);
	ft_printf("%c%s", RL_ESCAPE, RL_DELETE_TO_END);
	while (dir_info)
	{
		if (*dir_info->d_name != '.' && ft_strncmp(string, dir_info->d_name, \
			ft_strlen(string)) == 0)
		{
			ft_printf("%s ", dir_info->d_name);
			num_matches++;
		}
		dir_info = readdir(dir);
	}
	closedir(dir);
	return (num_matches);
}
