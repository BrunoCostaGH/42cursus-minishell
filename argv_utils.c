/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:04:04 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/19 16:34:42 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_token(t_data *data, int id)
{
	int	i;
	int	k;

	i = id;
	k = 0;
	data->argv.type[i - 1] = 0;
	free(data->argv.args[i][k]);
	data->argv.args[i][k] = 0;
	while (data->argv.args[i][++k])
		data->argv.args[i][k - 1] = data->argv.args[i][k];
	data->argv.args[i][k - 1] = 0;
	if ((--i >= 0 && data->argv.args[i] && !data->argv.args[i][0]) || \
		(++i >= 0 && data->argv.args[i] && !data->argv.args[i][0]))
	{
		free_darr((void **)data->argv.args[i]);
		while (data->argv.args[++i])
			data->argv.args[i - 1] = data->argv.args[i];
		data->argv.args[i - 1] = 0;
		i = id - 1;
		while (data->argv.type[++i])
			data->argv.type[i - 1] = data->argv.type[i];
		data->argv.type[i - 1] = 0;
	}
}

static void	regroup_argv_2(t_data *data, char **temp, int i_index)
{
	int	e_index;

	free_darr((void **)data->argv.args[i_index]);
	data->argv.args[i_index] = temp;
	e_index = i_index + 1;
	free_darr((void **)data->argv.args[e_index]);
	while (data->argv.args[++e_index])
		data->argv.args[e_index - 1] = data->argv.args[e_index];
	data->argv.args[e_index - 1] = 0;
	e_index = i_index;
	while (data->argv.type[++e_index])
		data->argv.type[e_index - 1] = data->argv.type[e_index];
	data->argv.type[e_index - 1] = 0;
}

void	regroup_argv(t_data *data)
{
	int		i;
	int		k;
	int		j;
	char	**temp;

	i = 0;
	while (data->argv.args[i + 1])
	{
		k = -1;
		j = 0;
		if (data->argv.type[i] == 0 && data->argv.args[i + 1][0])
		{
			temp = ft_calloc((darr_len((void **)data->argv.args[i]) \
			+ darr_len((void **)data->argv.args[i + 1]) + 1), (sizeof(char *)));
			if (!temp)
				return ;
			while (data->argv.args[i][++k])
				temp[k] = ft_strdup(data->argv.args[i][k]);
			while (data->argv.args[i + 1][j])
				temp[k++] = ft_strdup(data->argv.args[i + 1][j++]);
			regroup_argv_2(data, temp, i);
			continue ;
		}
		i++;
	}
}

void	print_argv(t_data *data, int id)
{
	int	i;
	int	j;

	i = id - 1;
	while (data->argv.args[++i])
	{
		j = -1;
		while (data->argv.args[i][++j])
		{
			fprintf(stderr, "%s ", data->argv.args[i][j]);
			fflush(stderr);
		}
		fprintf(stderr, "[%d](%s) ", i, get_token(data, i));
		fflush(stderr);
	}
	fprintf(stderr, "\n");
}
