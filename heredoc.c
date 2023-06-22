/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:05:44 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/06/22 20:07:26 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_data *data, int id)
{
	char	*str;

	init_tmp(data);
	open_file(data, data->tmp_file, O_CREAT | O_RDWR | O_TRUNC, \
	&data->file_io[0]);
	execute_sig_int(0, data);
	set_heredoc_handler();
	str = readline("heredoc> ");
	while (str != NULL)
	{
		if (*data->argv.args[id + 1] && \
		!ft_strncmp(data->argv.args[id + 1][0], \
		str, ft_strlen(data->argv.args[id + 1][0]) + 1))
			break ;
		write(data->file_io[0], str, ft_strlen(str));
		write(data->file_io[0], "\n", 1);
		str = readline("heredoc> ");
	}
	close(data->file_io[0]);
	data->file_io[0] = open(data->tmp_file, O_RDONLY);
	if (data->file_io[0] == -1)
		handle_error(data, data->tmp_file, 0);
}
