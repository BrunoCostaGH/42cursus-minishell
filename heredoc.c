/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:05:44 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/05 19:24:47 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_heredoc(t_data *data, int id)
{
	char	*str;

	execute_sig_int(0, data);
	set_heredoc_handler();
	while (1)
	{
		str = ft_readline("heredoc> ");
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
	reset_io(data);
	exit_shell(data, 0);
}

int	heredoc(t_data *data, int id)
{
	int		pid;

	init_tmp(data);
	open_file(data, data->tmp_file, 0100 | 02 | 01000, \
	&data->file_io[0]);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
		run_heredoc(data, id);
	while (waitpid(pid, 0, 1) == 0)
		;
	if (access(data->tmp_file, 0) != 0)
	{
		free(data->tmp_file);
		data->tmp_file = 0;
		return (2);
	}
	close(data->file_io[0]);
	data->file_io[0] = open(data->tmp_file, 00);
	if (data->file_io[0] == -1)
		handle_error(data, data->tmp_file, 0);
	return (1);
}
