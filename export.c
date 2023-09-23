/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:42:05 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/20 16:29:25 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_sorted_envp(t_data *data)
{
	int	id;

	if (data->envp.sorted_envp)
	{
		id = 0;
		while (data->envp.sorted_envp[id])
			free_darr((void **)data->envp.sorted_envp[id++]);
		free(data->envp.sorted_envp);
		data->envp.sorted_envp = 0;
	}
}

static int	check_argv(t_data *data, char *arg, int initial)
{
	int		index;

	index = 0;
	if (initial == TRUE && !arg)
	{
		clear_sorted_envp(data);
		data->envp.sorted_envp = ft_calloc(\
		darr_len((void **)data->envp.envp) + 1, sizeof(char **));
		if (!data->envp.sorted_envp)
			return (1);
		build_sorted_env(data, data->envp.sorted_envp);
		while (data->envp.sorted_envp[++index - 1])
		{
			ft_printf("declare -x %s", data->envp.sorted_envp[index - 1][0]);
			if (data->envp.sorted_envp[index - 1][1])
				ft_printf("=\"%s\"", data->envp.sorted_envp[index - 1][1]);
			ft_printf("\n");
		}
		return (1);
	}
	else if (initial == FALSE)
		if (check_identifier(data, "export", arg))
			return (1);
	return (0);
}

static void	do_export(t_data *data, char ***temp_envp, char **argv)
{
	int		i_argv;
	int		i_env;
	char	**temp;

	i_argv = 0;
	i_env = darr_len((void **)temp_envp);
	while (argv[++i_argv])
	{
		if (argv[i_argv][0] == '=' && check_argv(data, argv[i_argv], FALSE))
			continue ;
		temp = ft_split(argv[i_argv], '=');
		if (!check_argv(data, temp[0], FALSE))
		{
			temp_envp[i_env] = ft_calloc(2 + 1, sizeof(char *));
			if (!temp_envp[i_env])
				return ;
			temp_envp[i_env][0] = ft_strdup(temp[0]);
			if (temp[1])
				temp_envp[i_env][1] = ft_strdup(temp[1]);
			else if (ft_strchr(argv[i_argv], '='))
				temp_envp[i_env][1] = ft_calloc(1, sizeof(char));
		}
		free_darr((void **)temp);
		i_env++;
	}
}

void	export(t_data *data, char **argv)
{
	int		index_argv;
	int		argv_len;
	char	*_argv[3];
	char	***temp_envp;

	index_argv = 0;
	if (check_argv(data, argv[1], TRUE))
		return ;
	while (argv[++index_argv])
	{
		_argv[0] = argv[0];
		_argv[1] = argv[index_argv];
		_argv[2] = 0;
		argv_len = 1 - check_envp(data, _argv);
		data->exit_status = 0;
		if (!argv_len)
			continue ;
		temp_envp = duplicate_envp(data, argv_len);
		do_export(data, temp_envp, _argv);
		free(data->envp.envp);
		data->envp.envp = temp_envp;
	}
}
