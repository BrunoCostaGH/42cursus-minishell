/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:05:44 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/24 15:01:37 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_data *data, int **pipe_fd, int id)
{
	int		pid;
	char	*str;

	init_tmp(data);
	open_file(data, data->tmp_file, O_CREAT | O_RDWR | O_TRUNC, \
	&data->file_io[0]);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		execute_sig_int(0, data, pipe_fd);
		set_heredoc_handler();
		while (1)
		{
			str = readline("heredoc> ");
			if (!str || !ft_strncmp(data->argv.args[id + 1][0], \
			str, ft_strlen(data->argv.args[id + 1][0]) + 1))
				break ;
			check_variables(data, &str, FALSE);
			write(data->file_io[0], str, ft_strlen(str));
			write(data->file_io[0], "\n", 1);
			free(str);
		}
		if (str)
			free(str);
		str = 0;
		free(data->tmp_file);
		data->tmp_file = 0;
		exit_shell(data, 0);
	}
	waitpid(pid, 0, 0);
	close(data->file_io[0]);
	data->file_io[0] = open(data->tmp_file, O_RDONLY);
	if (data->file_io[0] == -1)
		handle_error(data, data->tmp_file, 0);
}
