/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:56:27 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/09/29 19:55:59 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell.h"

/*
 * RETURN VALUE
 * Returns a memory allocated string with the updated string
 */
static char	*ft_strerase(const char *string, size_t pos)
{
	char	*temp;
	char	*_return;

	if (!string && !pos)
		return (ft_strdup(string));
	else if (!string)
		return (0);
	temp = ft_calloc(pos + 1, sizeof(char));
	(void)ft_strlcpy(temp, string, pos);
	if ((size_t)ft_strlen(string) >= pos)
	{
		_return = ft_strjoin(temp, string + pos);
		free(temp);
	}
	else
		_return = temp;
	return (_return);
}

/*
 * RETURN VALUE
 * Returns a memory allocated string with the updated string
 */
static char	*ft_strinsert(const char *string, char *to_insert, size_t pos)
{
	char	*temp;
	char	*_return;

	if (!string && !pos)
		return (ft_strdup(to_insert));
	else if (!string)
		return (0);
	_return = ft_calloc(pos + 1, sizeof(char));
	(void)ft_strlcpy(_return, string, pos + 1);
	temp = ft_strjoin(_return, to_insert);
	if (_return)
		free(_return);
	if ((size_t)ft_strlen(string) >= pos)
	{
		_return = ft_strjoin(temp, string + pos);
		free(temp);
	}
	else
		_return = temp;
	return (_return);
}

/*
 * TODO add redraw of terminal window
 * TODO fix cursor after using tab [tab is disabled for now]
 * TODO add tab autocomplete
 */
static void	print_char(t_readline *rl_data, char *string)
{
	char	buf[3];

	if (!*string)
		return ;
	if (*string == '\x1b' && read(0, &buf[0], 1) && read(0, &buf[1], 1))
	{
		if (ft_tolower(buf[1]) == 'a')
			;//ft_printf("\x1b[1A");
		else if (ft_tolower(buf[1]) == 'b')
			;//ft_printf("\x1b[1B");
		else if (ft_tolower(buf[1]) == 'c' && rl_data->input && \
			rl_data->cursor_pos + 1 <= ft_strlen(rl_data->input))
		{
			ft_printf("\x1b[1C");
			rl_data->cursor_pos++;
		}
		else if (ft_tolower(buf[1]) == 'd' && rl_data->cursor_pos - 1 >= 0)
		{
			ft_printf("\x1b[1D");
			rl_data->cursor_pos--;
		}
		else if (ft_tolower(buf[1]) == '2')
			read(0, &buf[0], 1);
		else if (ft_tolower(buf[1]) == '3')
			;//TODO DELETE KEY
	}
	else if (*string == 0x7f && ft_strlen(rl_data->input))
	{
		//TODO implement ft_strerase();
		ft_printf("\b \b");
		rl_data->input[ft_strlen(rl_data->input) - 1] = 0;
	}
}

/*
 * RETURN VALUE
 * Returns a memory allocated string with the user input
 */
static void	get_user_input(t_readline *rl_data, const char *prompt)
{
	bool	_exit;
	char	*temp;
	char	buf[2];
	ssize_t	read_bytes;

	_exit = false;
	while (!_exit)
	{
		if (rl_data->input)
		{
			free(rl_data->input);
			rl_data->input = 0;
		}
		ft_printf("%s", prompt);
		read_bytes = read(0, &buf, 1);
		buf[read_bytes] = '\0';
		while (read_bytes > 0)
		{
			if (ft_isprint(buf[0]) || \
				(buf[0] >= 7 && buf[0] <= 13 && buf[0] != 9 && buf[0] != 10))
			{
				temp = rl_data->input;
				rl_data->input = ft_strinsert(rl_data->input, buf, \
					rl_data->cursor_pos);
				ft_printf("%s", rl_data->input + rl_data->cursor_pos);
				for (int i = rl_data->cursor_pos; i < ft_strlen(rl_data->input) - 1; i++)
				{
					ft_printf("\x1b[1D");
				}
				rl_data->cursor_pos++;
				if (temp)
					free(temp);
			}
			print_char(rl_data, &buf[0]);
			if ((buf[0] == '\n' && !rl_data->input))
			{
				ft_printf("\n");
				break ;
			}
			if (buf[0] == '\n' || (buf[0] == 0x04 && !rl_data->input))
			{
				_exit = true;
				break ;
			}
			read_bytes = read(0, &buf, 1);
			buf[read_bytes] = '\0';
		}
	}
}

/*
 * RETURN VALUE
 * Returns the current input, without waiting for user prompt
 */
static void	get_input(t_readline *rl_data, const char *prompt)
{
	struct termios	old;
	struct termios	new;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO | ECHOE);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	new.c_cc[VERASE] = 0;
	new.c_cc[VWERASE] = 0;
	new.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	get_user_input(rl_data, prompt);
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

char	*ft_readline(const char *prompt)
{
	t_readline		rl_data;

	rl_data.input = 0;
	rl_data.cursor_pos = 0;
	get_input(&rl_data, prompt);
	ft_printf("\n");
	return (rl_data.input);
}
