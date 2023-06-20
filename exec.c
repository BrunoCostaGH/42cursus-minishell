/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:13:32 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/20 15:30:05 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_error_status(t_data *data, char **argv)
{
	if ((data->exit_status >> 7) & 0x01)
		write(2, "minishell: Quit (core dump)\n", 28);
	else if (argv && access(argv[0], F_OK))
	{
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, ": command not found\n", 20);
		data->exit_status = 127;
		return ;
	}
	data->exit_status >>= 8;
}

static void	build_envp(t_data *data)
{
	int		len;
	char	*temp;

	len = 0;
	while (data->envp.envp[len] && data->envp.envp[len][1])
		len++;
	if (data->envp.exec_envp)
		free_darr((void **)data->envp.exec_envp);
	data->envp.exec_envp = ft_calloc(sizeof(char *), len + 1);
	if (!data->envp.exec_envp)
		return ;
	while (len > 0 && data->envp.envp[--len])
	{
		temp = ft_strjoin(data->envp.envp[len][0], "=");
		data->envp.exec_envp[len] = ft_strjoin(temp, data->envp.envp[len][1]);
		free(temp);
	}
}

/* Check if argv[0] is a file in any of the folders specified by $PATH and if
 * true return the program's path.
 */
static char	*check_environment(t_data *data, char *fname)
{
	int		i;
	char	*name;
	char	*path;
	char	**little_path;

	i = -1;
	name = 0;
	little_path = ft_split(get_env_var(data, "PATH"), ':');
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
		argv[0] = check_environment(data, argv[0]);
		build_envp(data);
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (!pid)
		{
			if (execve(argv[0], argv, data->envp.exec_envp) == -1)
				if (errno != 2)
					perror("Error");
			data->exit_status = 1;
			exit_shell(data, 0);
		}
		else
		{
			while (waitpid(pid, &data->exit_status, WUNTRACED) == -1)
				;
			set_error_status(data, argv);
		}
	}
}
