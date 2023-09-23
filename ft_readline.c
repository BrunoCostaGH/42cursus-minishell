/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:56:27 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/09/23 16:49:45 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "libft/libft.h"



char	*ft_readline(char *prompt)
{
	char	*temp;
	char	*_return;
	char	*buf;
	ssize_t	read_bytes;

	_return = ft_calloc(1, sizeof(char));
	buf = ft_calloc((42 + 1), sizeof(char));
	ft_printf("%s", prompt);
	read_bytes = read(0, buf, sizeof(buf));
	while (read_bytes > 0)
	{
		if (temp)
			free(temp);
		temp = ft_strjoin(_return, buf);
		if (_return)
			free(_return);
		_return = ft_strtrim(temp, "\n\r");
		if (read_bytes < (ssize_t) sizeof(buf))
			break ;
		read_bytes = read(0, buf, sizeof(buf));
	}
	free(buf);
	if (temp)
		free(temp);
	return (_return);
}
