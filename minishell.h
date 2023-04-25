/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:24:17 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/25 14:43:31 by bsilva-c         ###   ########.fr       */
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

typedef struct s_data
{
	int		exit_status;
	char	*prompt;
}	t_data;

char	*get_env_var(char *prompt);

char	**set_argv(const char *prompt);

void	pwd(void);
void	shell_exit(char *prompt);
void	free_darr(void **arr);
void	change_dir(char *prompt);
void	run_executable(char *prompt);

void	*init_struct(void);
void	*str_toupper(char *str);

#endif
