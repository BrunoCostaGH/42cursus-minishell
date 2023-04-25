/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:13:32 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/25 18:48:23 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if argv[0] is a file in any of the folders specified by $PATH and if
 * true return the program's path.
 */
static char	*check_environment(char *fname)
{
	int		i;
	char	*name;
	char	*path;
	char	**little_path;

	i = -1;
	name = 0;
	little_path = ft_split(getenv("PATH"), ':');
	while (little_path[++i])
	{
		path = ft_strjoin(little_path[i], "/");
		name = ft_strjoin(path, fname);
		free(path);
		if (access(name, F_OK) == 0)
			break ;
		free(name);
		name = 0;
	}
	if (name)
	{
		free(fname);
		fname = name;
	}
	free_darr((void **)little_path);
	return (fname);
}

void	run_executable(t_data *data)
{
	char	**argv;
	pid_t	pid;

	if (data->prompt && *data->prompt)
	{
		argv = set_argv(data->prompt);
		argv[0] = check_environment(argv[0]);
		pid = fork();
		if (!pid)
		{
			if (execve(argv[0], argv, NULL) == -1)
				perror("Error");
			exit(127);
		}
		else
		{
			if (pid == -1)
				perror("Error");
			else
				data->interactive = FALSE;
			while (waitpid(pid, &data->exit_status, 0) != -1)
				;
			data->interactive = TRUE;
			free_darr((void **)argv);
			data->exit_status >>= 8;
		}
	}
}
