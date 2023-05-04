/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:24:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/04 20:04:53 by bsilva-c         ###   ########.fr       */
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

/*	TYPES
 * 0 = regular
 * 1 = pipes
 * 2 = redirections
 * */
typedef struct s_args
{
	int		*type;
	char	**argv;
}	t_args;

typedef struct s_data
{
	int				interactive;
	int				exit_status;
	char			*prompt;
	char			**envp;
	struct s_args	argv;
}	t_data;

char	*get_env_var(t_data *data, const char *var_name);

void	env(t_data *data, char **argv);
void	set_s_argv(t_data *data);
void	pwd(t_data *data, char **argv);
void	echo(t_data *data, char **argv);
void	free_darr(void **arr);
void	set_argv(t_data *data);
void	set_handle_struct(void);
void	shell_exit(t_data *data);
void	change_dir(t_data *data, char **argv);
void	unset(t_data *data, char **argv);
void	check_variables(t_data *data);
void	export(t_data *data, char **argv);
void	find_command(t_data *data, char **argv);
void	execute_sig_action(int sig, void *data);
void	run_executable(t_data *data, char **argv);

int		check_for_pipes(t_data *data);

void	*init_struct(char **envp);
void	*str_toupper(char *str);

#endif
