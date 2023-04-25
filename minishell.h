/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:24:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/25 20:49:51 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef struct s_data
{
	int		interactive;
	int		exit_status;
	char	*prompt;
}	t_data;

char	*get_env_var(char *prompt);

char	**set_argv(const char *prompt);

void	pwd(void);
void	free_darr(void **arr);
void	shell_exit(t_data *data);
void	change_dir(char *prompt);
void	run_executable(t_data *data);
void	set_handle_struct(void);
void	execute_sig_action(int sig, void *data);

void	*init_struct(void);
void	*str_toupper(char *str);

#endif
