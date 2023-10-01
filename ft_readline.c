/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:56:27 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/01 20:03:22 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	m_rl_clear_history(void *p_data);
void	m_add_history(void *p_data, char *string);
void	m_rl_insert_text(void *p_data, char *text);
void	m_rl_delete_text(void *p_data, int start, int end);

/*
 * TODO add redraw of terminal window, for deleting multi-line prompts
 * TODO fix cursor after using tab [tab is disabled for now]
 * TODO add tab autocomplete
 */
static void	print_char(t_readline *rl_data, const char *string)
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
		else if (ft_tolower(buf[1]) == '2' && read(0, &buf[0], 1))
			;
		else if (ft_tolower(buf[1]) == '3' && read(0, &buf[0], 1) && \
			rl_data->input && ft_strlen(rl_data->input) > rl_data->cursor_pos)
		{
			(void)rl_delete_text(rl_data->cursor_pos, rl_data->cursor_pos);
			ft_printf("%s \b", rl_data->input + rl_data->cursor_pos);
			for (int i = rl_data->cursor_pos; i < ft_strlen(rl_data->input);
				 i++)
			{
				ft_printf("\x1b[1D");
			}
		}
	}
	else if (*string == 0x7f && rl_data->cursor_pos > 0)
	{
		(void)rl_delete_text(rl_data->cursor_pos - 1, rl_data->cursor_pos - 1);
		rl_data->cursor_pos--;
		ft_printf("\b \b%s \b", rl_data->input + rl_data->cursor_pos);
		for (int i = rl_data->cursor_pos; i < ft_strlen(rl_data->input); i++)
		{
			ft_printf("\x1b[1D");
		}
	}
}

/*
 * RETURN VALUE
 * Returns a memory allocated string with the user input
 */
static void	get_user_input(t_readline *rl_data, const char *prompt)
{
	bool	_exit;
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
				(void)rl_insert_text(buf);
				ft_printf("%s", rl_data->input + rl_data->cursor_pos);
				for (int i = rl_data->cursor_pos; i < ft_strlen(rl_data->input) - 1; i++)
				{
					ft_printf("\x1b[1D");
				}
				rl_data->cursor_pos++;
			}
			print_char(rl_data, &buf[0]);
			if ((buf[0] == '\n' && !rl_data->input))
			{
				ft_printf("\n");
				break ;
			}
			if (buf[0] == '\n' || (buf[0] == 0x04 && !rl_data->input))
			{
				ft_printf("%c", buf[0]);
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
	new.c_cc[VSUSP] = 0;
	new.c_cc[VLNEXT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	get_user_input(rl_data, prompt);
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

char	*ft_readline(const char *prompt)
{
	static t_readline	*rl_data;

	if (!rl_data)
		rl_data = malloc(sizeof(t_readline));
	rl_data->input = 0;
	rl_data->cursor_pos = 0;
	m_rl_delete_text(rl_data, 0, 0);
	m_rl_insert_text(rl_data, 0);
	m_add_history(rl_data, 0);
	m_rl_clear_history(rl_data);
	get_input(rl_data, prompt);
	return (rl_data->input);
}
