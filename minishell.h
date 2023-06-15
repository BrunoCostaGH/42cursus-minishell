/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:24:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/06/15 21:05:14 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
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
	char	***sorted_envp;
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
	int				*file_io;
	char			*prompt;
	char			*tmp_file;
	struct s_envp	envp;
	struct s_args	argv;
}	t_data;

int		darr_len(void **arr);
int		iarr_len(const int *arr);
int		check_tokens(t_data *data);
int		count_char(const char *prompt);
int		count_group(const char *prompt);
int		count_string(const char *prompt);
int		get_fd_out(t_data *data, int *fd);
int		check_envp(t_data *data, char **argv);
int		get_fd_in(t_data *data, int **pipe_fd);
int		handle_error(t_data *data, char *command, int error);
int		handle_quote(const char *prompt, int *index, int *quote);
int		check_identifier(t_data *data, char *command, char *arg);
int		check_for_special_char(t_data *data, const char *prompt, int *i, \
int id);

char	*get_token(t_data *data, int id);
char	*get_env_var(t_data *data, const char *var_name);

char	***duplicate_envp(t_data *data, int len);

void	pwd(t_data *data);
void	free_darr(void **arr);
void	init_tmp(t_data *data);
void	set_argv(t_data *data);
void	set_handle_struct(void);
void	clear_argv(t_data *data);
void	regroup_argv(t_data *data);
void	check_variables(t_data *data);
void	env(t_data *data, char **argv);
void	echo(t_data *data, char **argv);
void	unset(t_data *data, char **argv);
void	export(t_data *data, char **argv);
void	exit_shell(t_data *data, char **argv);
void	change_dir(t_data *data, char **argv);
void	find_command(t_data *data, char **argv);
void	execute_sig_action(int sig, void *data);
void	run_executable(t_data *data, char **argv);
void	set_error_status(t_data *data, char **argv);
void	build_sorted_env(t_data *data, char ***envp);


void	*init_struct(char **envp);

#endif
