/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:24:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/05/22 17:15:29 by bsilva-c         ###   ########.fr       */
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

# ifndef REGULAR
#  define REGULAR 0
# endif

/* | REDIRECT INPUT */
# ifndef PIPE
#  define PIPE 1
# endif

/* < REDIRECT INPUT */
# ifndef REDR_INPUT
#  define REDR_INPUT 3
# endif

/* > REDIRECT OUTPUT */
# ifndef REDR_OUTPUT
#  define REDR_OUTPUT 5
# endif

/* >> REDIRECT OUTPUT IN APPEND MODE*/
# ifndef REDR_APPEND
#  define REDR_APPEND 2
# endif

/* << REDIRECT UNTIL DELIMITER */
# ifndef REDR_DELIM
#  define REDR_DELIM 4
# endif

typedef struct s_envp
{
	char	**exec_envp;
	char	***envp;
}	t_envp;

typedef struct s_args
{
	int		*type;
	char	***args;
}	t_args;

typedef struct s_data
{
	int				interactive;
	int				exit_status;
	char			*prompt;
	struct s_envp	envp;
	struct s_args	argv;
}	t_data;

int		len_darr(void **arr);
int		check_for_pipes(t_data *data);
int		char_count(const char *prompt);
int		group_count(const char *prompt);
int		string_count(const char *prompt);
int		check_envp(t_data *data, char **argv);
int		handle_error(t_data *data, char *command, int error);
int		handle_quote(const char *prompt, int *index, int *quote);
int		check_identifier(t_data *data, char *command, char *arg);
int		check_for_special_char(t_data *data, const char *prompt, int *i, \
int id);

char	*get_env_var(t_data *data, const char *var_name);

char	***duplicate_envp(t_data *data, int len);

void	shell_error(void);
void	pwd(t_data *data);
void	free_darr(void **arr);
void	set_argv(t_data *data);
void	set_handle_struct(void);
void	argv_clear(t_data *data);
void	check_variables(t_data *data);
void	env(t_data *data, char **argv);
void	echo(t_data *data, char **argv);
void	unset(t_data *data, char **argv);
void	export(t_data *data, char **argv);
void	shell_exit(t_data *data, char **argv);
void	change_dir(t_data *data, char **argv);
void	find_command(t_data *data, char **argv);
void	execute_sig_action(int sig, void *data);
void	run_executable(t_data *data, char **argv);

void	*init_struct(char **envp);

#endif
