/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:13:32 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/04/27 17:54:53 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_error_status(t_data *data, char **argv)
{
	int	temp_error;

	temp_error = data->exit_status;
	if ((data->exit_status >> 7) & 0x01)
		write(2, "Quit (core dump)\n", 17);
	temp_error <<= 8;
	temp_error >>= 8;
	if (!temp_error && ((data->exit_status >> 8)))
		data->exit_status >>= 8;
	else
		data->exit_status = temp_error;
	if (errno == 2)
	{
		write(2, "command not found: ", 19);
		write(2, argv[0], ft_strlen(argv[0]));
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

void	run_executable(t_data *data, char **argv)
{
	pid_t	pid;

	if (argv && *argv)
	{
		argv[0] = check_environment(argv[0]);
		pid = fork();
		if (pid == -1)
			perror("Error");
		errno = 0;
		if (!pid)
		{
			if (execve(argv[0], argv, data->envp) == -1)
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
			set_error_status(data, argv);
		}
	}
}
