/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:58:39 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/02 15:36:02 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <termios.h>
# include "libft/libft.h"
# include <stdbool.h>

typedef struct s_readline
{
	t_list			**history;
	unsigned int	history_offset;
	char			*input;
	int				cursor_offset;
}	t_readline;

char	*ft_readline(const char *prompt);

int		rl_insert_text(char *text);
int		rl_delete_text(int start, int end);

void	rl_clear_history(void);
void	add_history(char *string);

#endif /* FT_READLINE_H */
