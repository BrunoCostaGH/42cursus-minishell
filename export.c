/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:42:05 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/21 18:27:43 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_argv(t_data *data, char *arg, int initial)
{
	int		index;

	index = 0;
	if (initial == TRUE && !arg)
	{
		while (data->envp.envp[++index])
		{
			printf("%s %s", "declare -x", data->envp.envp[index - 1][0]);
			if (data->envp.envp[index - 1][1])
				printf("=\"%s\"", data->envp.envp[index - 1][1]);
			printf("\n");
		}
		return (1);
	}
	else if ((initial == TRUE && !*arg) || initial == FALSE)
		if (check_identifier(data, "export", arg))
			return (1);
	return (0);
}

static char	***duplicate_envp(t_data *data, int len)
{
	int		i;
	char	***temp_envp;

	i = 0;
	temp_envp = ft_calloc(len + len_darr((void **)data->envp.envp) + 1, \
	sizeof(char **));
	while (data->envp.envp[i])
	{
		temp_envp[i] = ft_calloc(2, sizeof(char *));
		temp_envp[i][0] = ft_strdup(data->envp.envp[i][0]);
		if (data->envp.envp[i][1])
			temp_envp[i][1] = ft_strdup(data->envp.envp[i][1]);
		free_darr((void **)data->envp.envp[i]);
		i++;
	}
	return (temp_envp);
}

static int	edit_existing_envp(t_data *data, char **argv)
{
	int		i;
	int		index_argv;
	int		amount_edited;
	char	**temp;

	amount_edited = 0;
	index_argv = 0;
	while (argv[++index_argv])
	{
		i = 0;
		temp = ft_split(argv[index_argv], '=');
		while (*temp && data->envp.envp[i] && ft_strncmp(data->envp.envp[i][0], \
		temp[0], ft_strlen(data->envp.envp[i][0])))
			i++;
		if (data->envp.envp[i])
		{
			free(data->envp.envp[i][1]);
			data->envp.envp[i][1] = 0;
			if (temp[1])
				data->envp.envp[i][1] = ft_strdup(temp[1]);
			free(argv[index_argv]);
			i = index_argv;
			while (argv[++i])
				argv[i - 1] = argv[i];
			argv[--i] = 0;
			amount_edited++;
		}
		free_darr((void **)temp);
	}
	return (amount_edited);
}

void	export(t_data *data, char **argv)
{
	int		index_argv;
	int		index_env;
	char	**temp;
	char	***temp_envp;

	if (check_argv(data, argv[1], TRUE))
		return ;
	index_argv = len_darr((void **)argv) - edit_existing_envp(data, argv);
	if (!index_argv)
		return ;
	temp_envp = duplicate_envp(data, index_argv);
	index_env = len_darr((void **)temp_envp);
	index_argv = 0;
	while (argv[++index_argv])
	{
		temp = ft_split(argv[index_argv], '=');
		if (check_argv(data, temp[0], FALSE))
		{
			free_darr((void **)temp);
			continue ;
		}
		temp_envp[index_env] = ft_calloc(2, sizeof(char *));
		temp_envp[index_env][0] = ft_strdup(temp[0]);
		if (temp[1])
			temp_envp[index_env][1] = ft_strdup(temp[1]);
		free_darr((void **)temp);
		index_env++;
	}
	free(data->envp.envp);
	data->envp.envp = temp_envp;
}
