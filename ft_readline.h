/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:58:39 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/10/07 18:20:51 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include "libft/libft.h"
# include <stdio.h>
# include <dirent.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <sys/types.h>

# ifndef RL_ESCAPE
#  define RL_ESCAPE 27
# endif

# ifndef RL_SAVE_POS
#  define RL_SAVE_POS "7"
# endif

# ifndef RL_RESTORE_POS
#  define RL_RESTORE_POS "8"
# endif

# ifndef RL_DELETE_TO_END
#  define RL_DELETE_TO_END "[0J"
# endif


# ifndef RL_MOVE_UP
#  define RL_MOVE_UP "[A"
# endif

# ifndef RL_MOVE_DOWN
#  define RL_MOVE_DOWN "[B"
# endif

# ifndef RL_MOVE_LEFT
#  define RL_MOVE_LEFT "[D"
# endif

# ifndef RL_MOVE_RIGHT
#  define RL_MOVE_RIGHT "[C"
# endif

# ifndef RL_INSERT_KEY
#  define RL_INSERT_KEY "[2"
# endif

# ifndef RL_DELETE_KEY
#  define RL_DELETE_KEY "[3"
# endif

typedef struct s_readline
{
	t_list			**history;
	unsigned int	history_offset;
	char			*input;
	int				cursor_offset;
}	t_readline;

char	*ft_readline(const char *prompt);
char	*ft_rl_print_autocomplete(char *string);

int		ft_rl_insert_text(char *text);
int		ft_rl_autocomplete(char *string);
int		ft_rl_delete_text(int start, int end);

void	ft_rl_clear_history(void);
void	ft_add_history(char *string);

#endif /* FT_READLINE_H */
