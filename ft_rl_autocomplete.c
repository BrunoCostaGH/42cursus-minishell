/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rl_autocomplete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:26:20 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/07 20:33:22 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static unsigned int	get_term_width(void)
{
	struct winsize	ws;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) != 0 && \
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != 0 && \
		ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) != 0)
	{
		perror("ioctl()");
		return (0);
	}
	return (ws.ws_col);
}

static void	free_darr(void **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = 0;
			i++;
		}
		free(arr);
		arr = 0;
	}
}

static int	darr_len(void **arr)
{
	int	i;

	i = 0;
	if (arr)
		while (arr[i])
			i++;
	return (i);
}

// TODO fix missing last file when printing to terminal
char	*ft_rl_print_autocomplete(char *string)
{
	static char	**file_arr;
	char		**temp;
	char		*_string;
	int			col_width[2];
	int			col_amount;
	int			index[2];

	index[0] = 0;
	col_width[0] = 0;
	if (string)
	{
		if (!file_arr)
		{
			file_arr = ft_calloc(2, sizeof(char *));
			file_arr[index[0]] = ft_strdup(string);
		}
		else
		{
			temp = ft_calloc(darr_len((void **)file_arr) + 1, sizeof(char *));
			while (file_arr[index[0]])
			{
				temp[index[0]] = ft_strdup(file_arr[index[0]]);
				index[0]++;
			}
			free_darr((void **)file_arr);
			file_arr = ft_calloc(index[0] + 2, sizeof(char *));
			index[0] = 0;
			index[1] = 0;
			_string = string;
			while (temp[index[0]])
			{
				if (_string && \
					ft_strncmp(_string, temp[index[0]], ft_strlen(_string)) < 0)
				{
					file_arr[index[1]++] = ft_strdup(_string);
					_string = 0;
					continue ;
				}
				file_arr[index[1]++] = ft_strdup(temp[index[0]++]);
			}
			if (_string)
				file_arr[index[1]] = ft_strdup(_string);
			free_darr((void **)temp);
		}
	}
	else if (file_arr && darr_len((void **)file_arr) == 1)
	{
		_string = ft_strdup(*file_arr);
		free_darr((void **)file_arr);
		file_arr = 0;
		return (_string);
	}
	else if (file_arr && darr_len((void **)file_arr) > 1)
	{
		while (file_arr[index[0]])
		{
			if (ft_strlen(file_arr[index[0]]) > col_width[0])
				col_width[0] = ft_strlen(file_arr[index[0]]) + 2;
			index[0]++;
		}
		index[0] = 0;
		while (index[0] <= (darr_len((void **)file_arr) / \
			((int)get_term_width() / col_width[0])))
		{
			index[1] = index[0];
			col_amount = ((int)get_term_width() / col_width[0]) + 1;
			while (--col_amount > 0 && index[1] < darr_len((void **)file_arr))
			{
				ft_printf("%s", file_arr[index[1]]);
				col_width[1] = col_width[0] - ft_strlen(file_arr[index[1]]);
				while (col_width[1]-- > 0)
					ft_printf(" ");
				index[1] += (darr_len((void **)file_arr) / \
					((int)get_term_width() / col_width[0]));
			}
			ft_printf("\n");
			index[0]++;
		}
		free_darr((void **)file_arr);
		file_arr = 0;
	}
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
			(void)ft_rl_print_autocomplete(dir_info->d_name);
			num_matches++;
		}
		dir_info = readdir(dir);
	}
	closedir(dir);
	return (num_matches);
}
