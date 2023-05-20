/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:10:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/20 20:04:23 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env(t_data *data, char *old_path, char *path)
{
	char	*argv[3];

	argv[0] = ft_strdup("export");
	argv[1] = ft_strjoin("OLDPWD=", old_path);
	argv[2] = NULL;
	export(data, argv);
	free(argv[1]);
	argv[1] = ft_strjoin("PWD=", path);
	export(data, argv);
	free(argv[0]);
	free(argv[1]);
}

void	change_dir(t_data *data, char **argv)
{
	char	*old_path;
	char	*path;

	if (argv[1] && argv[2])
	{
		handle_error(data, argv[0], 1);
		return ;
	}
	path = argv[1];
	if (!path)
		path = get_env_var(data, "HOME");
	old_path = get_env_var(data, "PWD");
	if (chdir(path) == -1)
	{
		perror("Error");
		data->exit_status = errno;
		return ;
	}
	update_env(data, old_path, getcwd(NULL, 0));
	data->exit_status = 0;
}
