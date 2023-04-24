/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:13:32 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/24 15:20:53 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Check if argv[0] is an environment variable and if true set argv[0] as the
 * address in the environment.
 */
static void	check_environment(void *path)
{
	char	*env;
	char	*final_path;

	if (!path)
		return ;
	env = ft_calloc(ft_strlen(path) + 1, sizeof(char));
	if (!env)
		return ;
	env = (char *)ft_memcpy(env, path, ft_strlen(path));
	env = (char *)str_toupper(env);
	final_path = getenv(env);
	if (final_path)
	{
		free(path);
		path = final_path;
	}
	free(env);
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
