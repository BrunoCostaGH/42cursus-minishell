/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:56:27 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/09/25 19:59:44 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "libft/libft.h"

//TODO write multi-line to prompt
char	*ft_readline(char *prompt)
{
	char	*temp;
	char	*_return;
	char	*buf;
	ssize_t	read_bytes;

	temp = 0;
	_return = ft_calloc(1, sizeof(char));
	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	ft_printf("%s", prompt);
	read_bytes = read(0, buf, 1);
	buf[read_bytes] = '\0';
	while (read_bytes > 0)
	{
		if (temp)
			free(temp);
		temp = ft_fndnrepl(buf, "\n", "\0");
		_return = ft_strjoin(_return, temp);
		if (ft_strchr(buf, '\n'))
			break ;
		read_bytes = read(0, buf, 1);
		buf[read_bytes] = '\0';
	}
	write(0, "\n", 1);
	free(buf);
	if (temp)
		free(temp);
	return (_return);
}
