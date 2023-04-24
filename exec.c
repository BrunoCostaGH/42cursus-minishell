/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:13:32 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/24 18:55:57 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if argv[0] is an environment variable and if true set argv[0] as the
 * address in the environment.
 */
static char	*check_environment(char *fname)
{
	int		i;
	char	*name;
	char	*path;
	char	**little_path;

	i = 0;
	name = 0;
	path = getenv("PATH");
	little_path = ft_split(path, ':');
	while (little_path[i])
	{
		path = ft_strjoin(little_path[i], "/");
		name = ft_strjoin(path, fname);
		free(path);
		if (access(name, F_OK) == 0)
			break ;
		free(name);
		name = 0;
		i++;
	}
	if (name)
	{
		free(fname);
		fname = name;
	}
	free_darr((void **)little_path);
	return (name);
}

void	run_executable(char *prompt)
{
	char	**argv;
	pid_t	pid;

	if (prompt && *prompt)
	{
		argv = set_argv(prompt);
		check_environment(argv[0]);
		pid = fork();
		if (!pid)
		{
			if (execve(argv[0], argv, NULL) == -1)
				perror("Error");
			exit(0);
		}
		else
		{
			if (pid == -1)
				perror("Error");
			while (waitpid(-1, NULL, 0) != -1)
				;
			free_darr((void **)argv);
		}
	}
}
