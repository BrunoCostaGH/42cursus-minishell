/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:56:27 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/09/26 19:51:27 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h> /* tcgetattr() and tcsetattr() */
#include "libft/libft.h"

/*
 * RETURN VALUE
 * Returns a malloc'd string with the user input;
 */
static char	*get_user_input(void)
{
	char	*temp;
	char	*_return;
	char	*buf;
	ssize_t	read_bytes;

	_return = ft_calloc(1, sizeof(char));
	buf = ft_calloc(2, sizeof(char));
	read_bytes = read(0, buf, 1);
	buf[read_bytes] = '\0';
	while (read_bytes > 0)
	{
		temp = _return;
		_return = ft_strjoin(temp, buf);
		if (temp)
			free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
		read_bytes = read(0, buf, 1);
		buf[read_bytes] = '\0';
	}
	free(buf);
	return (_return);
}

/*
 * RETURN VALUE
 * Returns the current input, without waiting for user prompt
 */
static char	*get_current_input(void)
{
	struct termios	old;
	struct termios	new;
	char			*ch;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~ICANON;
	new.c_cc[VMIN] = 0;
	new.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	ch = get_user_input();
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return (ch);
}

//TODO on multi-line, only display the text that is executing and
// not the whole block
char	*ft_readline(char *prompt)
{
	char	*temp[2];
	char	*_return;

	ft_printf("%s", prompt);
	temp[0] = get_current_input();
	if (ft_strlen(temp[0]) > 0 && ft_strchr(temp[0], '\n'))
	{
		ft_printf("%s", temp[0]);
		_return = ft_fndnrepl(temp[0], "\n", "\0");
		free(temp[0]);
		return (_return);
	}
	ft_printf("%s", temp[0]);
	temp[1] = get_user_input();
	_return = ft_strjoin(temp[0], temp[1]);
	free(temp[0]);
	temp[0] = ft_fndnrepl(_return, "\n", "\0");
	free(_return);
	free(temp[1]);
	return (temp[0]);
}
