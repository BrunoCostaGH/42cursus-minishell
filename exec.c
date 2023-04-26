/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:13:32 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/26 17:44:17 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_error_status(t_data *data)
{
	if ((data->exit_status >> 7) & 0x01)
		write(2, "Quit (core dump)\n", 17);
	data->exit_status <<= 8;
	data->exit_status >>= 8;
	if (errno == 2)
	{
		write(2, "command not found: ", 19);
		write(2, data->argv[0], ft_strlen(data->argv[0]));
		write(2, "\n", 1);
		data->exit_status = 127;
	}
}

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
	pid_t	pid;

	if (data->prompt && *data->prompt)
	{
		data->argv[0] = check_environment(data->argv[0]);
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (!pid)
		{
			if (execve(data->argv[0], data->argv, data->envp) == -1)
				if (errno != 2)
					perror("Error");
			exit(1);
		}
		else
		{
			data->interactive = FALSE;
			while (waitpid(pid, &data->exit_status, WUNTRACED) == -1)
				;
			data->interactive = TRUE;
			set_error_status(data);
		}
	}
}
