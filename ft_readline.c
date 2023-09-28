/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:56:27 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/09/28 19:52:35 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell.h"

/*
 * RETURN VALUE
 * Returns a memory allocated string with the updated string
 */
static char	*ft_strinsert(const char *string, char *to_insert, size_t pos)
{
	char	*temp;
	char	*_return;

	_return = ft_calloc(pos + 1, sizeof(char));
	(void)ft_strlcpy(_return, string, pos + 1);
	temp = ft_strjoin(_return, to_insert);
	if (_return)
		free(_return);
	_return = ft_strjoin(temp, string + pos);
	if (temp)
		free(temp);
	return (_return);
}

/* TODO
 * fix printing after writing within string
 * fix cursor after using tab [tab is disabled for now]
 * add history
 * add tab autocomplete
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
		else if (ft_tolower(buf[1]) == 'c' && \
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
			;//TODO INSERT KEY
		else if (ft_tolower(buf[1]) == '3')
			;//TODO DELETE KEY
	}
	else if (*string == 0x04)
		*string = 0;
	else if (*string == 0x7f && ft_strlen(rl_data->input))
	{
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
			free(rl_data->input);
		rl_data->input = ft_calloc(1, sizeof(char));
		if (!rl_data->input)
			return ;
		ft_printf("%s", prompt);
		read_bytes = read(0, &buf, 1);
		buf[read_bytes] = '\0';
		while (read_bytes > 0)
		{
			if (ft_isprint(buf[0]) || (buf[0] >= 7 && buf[0] <= 13 && buf[0] != 9))
			{
				temp = rl_data->input;
				rl_data->input = ft_strinsert(rl_data->input, buf, rl_data->cursor_pos);
				for (int i = rl_data->cursor_pos; i < ft_strlen(rl_data->input) - 1; i++)
				{
					ft_printf("\x1b[1D");
				}
				ft_printf("%s", rl_data->input + rl_data->cursor_pos);
				rl_data->cursor_pos++;
				free(temp);
			}
			print_char(rl_data, &buf[0]);
			if (ft_strchr(buf, '\n') || \
				(buf[0] == 0 && !ft_strlen(rl_data->input)))
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
static char	*get_input(const char *prompt)
{
	struct termios	old;
	struct termios	new;
	t_readline		rl_data;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO | ECHOE);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	new.c_cc[VERASE] = 0;
	new.c_cc[VWERASE] = 0;
	new.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	rl_data.input = 0;
	rl_data.cursor_pos = 0;
	get_user_input(&rl_data, prompt);
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return (rl_data.input);
}

char	*ft_readline(const char *prompt)
{
	char	*temp;
	char	*_return;

	temp = get_input(prompt);
	_return = ft_fndnrepl(temp, "\n", "\0");
	free(temp);
	return (_return);
}
