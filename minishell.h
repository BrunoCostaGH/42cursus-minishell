/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:24:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/28 13:59:49 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <dirent.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	char	**envp;
	char	**argv;
}	t_data;


char	*get_env_var(char *data);

void	env(t_data *data);
void	pwd(t_data *data);
void	echo(t_data *data);
void	free_darr(void **arr);
void	set_argv(t_data *data);
void	set_handle_struct(void);
void	shell_exit(t_data *data);
void	change_dir(t_data *data);
void	check_variables(t_data *data);
void	execute_sig_action(int sig, void *data);
void	run_executable(t_data *data, char **argv);

void	*init_struct(char **envp);
void	*str_toupper(char *str);

#endif
