/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:24:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/25 18:31:47 by bsilva-c         ###   ########.fr       */
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

typedef struct s_data
{
	int		exit_status;
	char	*prompt;
	char	**envp;
}	t_data;

int		get_exit_status(t_data *data);

char	*get_env_var(t_data *data);

char	**set_argv(const char *prompt);

void	env(char **envp);
void	pwd(t_data *data);
void	free_darr(void **arr);
void	shell_exit(t_data *data);
void	change_dir(t_data *data);
void	run_executable(t_data *data);

void	*init_struct(char **envp);
void	*str_toupper(char *str);

#endif
