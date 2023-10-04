/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:58:39 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/04 14:30:57 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include "libft/libft.h"
# include <termios.h>
# include <stdbool.h>
# include <sys/types.h>
# include <dirent.h>

typedef struct s_readline
{
	t_list			**history;
	unsigned int	history_offset;
	char			*input;
	int				cursor_offset;
}	t_readline;

char	*ft_rl_autocomplete(char *string);
char	*ft_readline(const char *prompt);

int		ft_rl_insert_text(char *text);
int		ft_rl_delete_text(int start, int end);

void	ft_rl_clear_history(void);
void	ft_add_history(char *string);

#endif /* FT_READLINE_H */
