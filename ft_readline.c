/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:56:27 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/09/27 00:57:50 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "libft/libft.h"

/* TODO
 * fix text overwrite with arrow keys
 * add delete key
 */
static void	print_char(char *_return, char c)
{
	char	buf[2];

	if (!c)
		return ;
	if (c == '\x1b')
	{
		read(0, &buf[0], 1);
		read(0, &buf[1], 1);
		/*if (ft_tolower(buf[1]) == 'a')
			;//ft_printf("\x1b[1A");
		else if (ft_tolower(buf[1]) == 'b')
			;//ft_printf("\x1b[1B");
		else if (ft_tolower(buf[1]) == 'c')
			;//ft_printf("\x1b[1C");
		else if (ft_tolower(buf[1]) == 'd')
			;//ft_printf("\x1b[1D");*/
	}
	else if (c == 0x7f)
	{
		ft_printf("\b \b");
		_return[ft_strlen(_return) - 2] = 0;
		return ;
	}
	else
	{
		ft_printf("%c", _return[ft_strlen(_return) - 1]);
		return ;
	}
	_return[ft_strlen(_return) - 1] = 0;
}

/*
 * RETURN VALUE
 * Returns a memory allocated string with the user input
 */
static char	*get_user_input(void)
{
	char	*temp;
	char	*_return;
	char	buf[1];
	ssize_t	read_bytes;

	_return = ft_calloc(1, sizeof(char));
	read_bytes = read(0, &buf, 1);
	buf[read_bytes] = '\0';
	while (read_bytes >= 0)
	{
		temp = _return;
		_return = ft_strjoin(temp, buf);
		if (temp)
			free(temp);
		print_char(_return, *buf);
		if (ft_strchr(buf, '\n'))
			break ;
		read_bytes = read(0, &buf, 1);
		buf[read_bytes] = '\0';
	}
	return (_return);
}

/*
 * RETURN VALUE
 * Returns the current input, without waiting for user prompt
 */
static char	*get_input(void)
{
	struct termios	old;
	struct termios	new;
	char			*ch;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO | ECHOE);
	new.c_cc[VMIN] = 0;
	new.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	ch = get_user_input();
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return (ch);
}

/*
 * TODO
 * fix prompt able to be overwritten or deleted
 */

char	*ft_readline(char *prompt)
{
	char	*temp;
	char	*_return;

	ft_printf("%s", prompt);
	temp = get_input();
	_return = ft_fndnrepl(temp, "\n", "\0");
	free(temp);
	return (_return);
}
