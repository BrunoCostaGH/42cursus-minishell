/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:56:27 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/05 21:33:01 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	m_rl_clear_history(void *p_data);
void	m_add_history(void *p_data, char *string);
void	m_rl_insert_text(void *p_data, char *text);
void	m_rl_delete_text(void *p_data, int start, int end);
char	*previous_history(t_readline *rl_data);
char	*next_history(t_readline *rl_data);

static void	clear_prompt(t_readline *rl_data)
{
	ft_printf("%s%s%s%s", RL_ESCAPE, RL_RESTORE_POS, \
							RL_ESCAPE, RL_DELETE_TO_END);
	if (rl_data->input)
		free(rl_data->input);
	rl_data->input = 0;
	rl_data->cursor_offset = 0;
}

static void	reset_cursor(t_readline *rl_data)
{
	int	index;

	index = 0;
	ft_printf("%s%s", RL_ESCAPE, RL_RESTORE_POS);
	while (index++ < rl_data->cursor_offset)
	{
		ft_printf("%s%s", RL_ESCAPE, RL_MOVE_RIGHT);
	}
}

/*
 * TODO fix cursor after using tab [tab is disabled for now]
 */
static void	print_char(t_readline *rl_data, const char *string)
{
	int		n;
	char	buf[3];
	char	*temp;

	if (!*string)
		return ;
	if (*string == *RL_ESCAPE && read(0, &buf[0], 1) && read(0, &buf[1], 1))
	{
		if (buf[0] == RL_MOVE_UP[0] && ft_toupper(buf[1]) == RL_MOVE_UP[1])
		{
			temp = previous_history(rl_data);
			if (temp)
			{
				clear_prompt(rl_data);
				rl_data->input = ft_strdup(temp);
				rl_data->cursor_offset = ft_strlen(rl_data->input);
				ft_printf("%s", rl_data->input);
			}
		}
		else if (buf[0] == RL_MOVE_DOWN[0] && \
			ft_toupper(buf[1]) == RL_MOVE_DOWN[1])
		{
			temp = next_history(rl_data);
			clear_prompt(rl_data);
			if (temp)
			{
				rl_data->input = ft_strdup(temp);
				rl_data->cursor_offset = ft_strlen(rl_data->input);
				ft_printf("%s", rl_data->input);
			}
		}
		else if (buf[0] == RL_MOVE_RIGHT[0] && \
			ft_toupper(buf[1]) == RL_MOVE_RIGHT[1] && rl_data->input && \
			rl_data->cursor_offset + 1 <= ft_strlen(rl_data->input))
		{
			ft_printf("%s%s", RL_ESCAPE, RL_MOVE_RIGHT);
			rl_data->cursor_offset++;
		}
		else if (buf[0] == RL_MOVE_LEFT[0] && \
			ft_toupper(buf[1]) == RL_MOVE_LEFT[1] && \
			rl_data->cursor_offset - 1 >= 0)
		{
			ft_printf("%s%s", RL_ESCAPE, RL_MOVE_LEFT);
			rl_data->cursor_offset--;
		}
		else if (buf[0] == RL_INSERT_KEY[0] && \
			ft_toupper(buf[1]) == RL_INSERT_KEY[1] && read(0, &buf[0], 1))
			;
		else if (buf[0] == RL_DELETE_KEY[0] && \
			ft_toupper(buf[1]) == RL_DELETE_KEY[1] && read(0, &buf[0], 1) && \
			rl_data->input && \
			ft_strlen(rl_data->input) > rl_data->cursor_offset)
		{
			ft_rl_delete_text(rl_data->cursor_offset, rl_data->cursor_offset);
			if (!rl_data->input)
			{
				ft_printf(" \b");
				return ;
			}
			ft_printf("%s \b", rl_data->input + rl_data->cursor_offset);
			for (int i = rl_data->cursor_offset; i < ft_strlen(rl_data->input); i++)
			{
				ft_printf("%s%s", RL_ESCAPE, RL_MOVE_LEFT);
			}
		}
	}
	else if ((*string == 8 || *string == 127) && rl_data->cursor_offset > 0)
	{
		ft_rl_delete_text(rl_data->cursor_offset - 1, \
			rl_data->cursor_offset - 1);
		rl_data->cursor_offset--;
		if (!rl_data->input)
		{
			ft_printf("\b \b");
			return ;
		}
		ft_printf("\b \b%s \b", rl_data->input + rl_data->cursor_offset);
		for (int i = rl_data->cursor_offset; i < ft_strlen(rl_data->input); i++)
		{
			ft_printf("%s%s", RL_ESCAPE, RL_MOVE_LEFT);
		}
	}
	else if (*string == 9 && rl_data->input && \
		rl_data->cursor_offset == ft_strlen(rl_data->input))
	{
		ft_printf("\n");
		n = 0;
		if (ft_strrchr(rl_data->input, ' '))
			while (rl_data->input + n != ft_strrchr(rl_data->input, ' ') \
					+ 1)
				n++;
		if (ft_strrchr(rl_data->input + n, '/'))
			while (rl_data->input + n != ft_strrchr(rl_data->input, '/') \
					+ 1)
				n++;
		if (!*(rl_data->input + n))
		{
			reset_cursor(rl_data);
			return ;
		}
		n = ft_rl_autocomplete(rl_data->input + n);
		if (n == 1)
		{
			n = 0;
			if (ft_strrchr(rl_data->input, ' '))
				while (rl_data->input + n != ft_strrchr(rl_data->input, ' ') \
					+ 1)
					n++;
			if (ft_strrchr(rl_data->input + n, '/'))
				while (rl_data->input + n != ft_strrchr(rl_data->input, '/') \
					+ 1)
					n++;
			rl_data->cursor_offset = n;
			temp = ft_rl_input_autocomplete(rl_data->input + n);
			ft_rl_delete_text(n, ft_strlen(rl_data->input) - 1);
			ft_rl_insert_text(temp);
			ft_printf("%s%s", RL_ESCAPE, RL_RESTORE_POS);
			ft_printf("%s%s%s", RL_ESCAPE, RL_DELETE_TO_END, rl_data->input);
			free(temp);
			rl_data->cursor_offset = ft_strlen(rl_data->input);
		}
		reset_cursor(rl_data);
	}
	else if ((*string == 9 && rl_data->cursor_offset == 0) || *string == 10)
	{
		if (rl_data->input)
			rl_data->cursor_offset = ft_strlen(rl_data->input);
		reset_cursor(rl_data);
		ft_printf("%s%s", RL_ESCAPE, RL_DELETE_TO_END);
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
			free(rl_data->input);
		rl_data->input = 0;
		rl_data->cursor_offset = 0;
		rl_data->history_offset = 0;
		ft_printf("%s", prompt);
		ft_printf("%s%s", RL_ESCAPE, RL_SAVE_POS);
		read_bytes = read(0, &buf, 1);
		buf[read_bytes] = '\0';
		while (read_bytes > 0)
		{
			if (ft_isprint(buf[0]))
			{
				(void)ft_rl_insert_text(buf);
				ft_printf("%s", rl_data->input + rl_data->cursor_offset);
				for (int i = rl_data->cursor_offset; i < ft_strlen(rl_data->input) - 1; i++)
				{
					ft_printf("%s%s", RL_ESCAPE, RL_MOVE_LEFT);
				}
				rl_data->cursor_offset++;
			}
			print_char(rl_data, &buf[0]);
			if ((buf[0] == 10 && rl_data->input) || \
				(buf[0] == 4 && !rl_data->input))
				_exit = true;
			if (_exit || buf[0] == 10)
				break ;
			read_bytes = read(0, &buf, 1);
			buf[read_bytes] = '\0';
		}
		if (rl_data->input)
			rl_data->cursor_offset = ft_strlen(rl_data->input);
		reset_cursor(rl_data);
		ft_printf("%s%s", RL_ESCAPE, RL_DELETE_TO_END);
		if (buf[0] == 10 || !_exit)
			ft_printf("\n");
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

	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	new.c_cc[VERASE] = 0;
	new.c_cc[VQUIT] = 0;
	new.c_cc[VSUSP] = 0;
	tcsetattr(0, TCSANOW, &new);
	get_user_input(rl_data, prompt);
	tcsetattr(0, TCSANOW, &old);
}

char	*ft_readline(const char *prompt)
{
	static t_readline	rl_data;

	rl_data.input = 0;
	m_rl_delete_text(&rl_data, 0, 0);
	m_rl_insert_text(&rl_data, 0);
	m_add_history(&rl_data, 0);
	m_rl_clear_history(&rl_data);
	get_input(&rl_data, prompt);
	return (rl_data.input);
}
