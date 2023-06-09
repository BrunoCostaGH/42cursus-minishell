# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/20 19:20:05 by bsilva-c          #+#    #+#              #
#    Updated: 2023/06/23 14:54:04 by bsilva-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Werror -Wextra
DEPS=libft/libft.a

SRCS=main.c free_n_exit.c exec.c pwd.c change_dir.c set_argv.c set_argv_utils.c\
minishell_utils.c init.c env.c signals.c variables.c pipes_n_redir.c echo.c\
error.c export.c export_utils.c pipes_n_redir_utils.c argv_utils.c ft_chrjoin.c\
heredoc.c heredoc_signals.c variables_utils.c

OBJS=$(SRCS:.c=.o)
NAME=minishell

LIBFT=libft/libft.a

all: deps $(NAME)
deps:
	$(MAKE) -C ./libft
$(NAME): $(OBJS) $(DEPS)
	@$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
clean:
	$(MAKE) $@ -C ./libft
	@rm $(OBJS)
fclean: clean
	$(MAKE) $@ -C ./libft
	@rm $(NAME)
re: fclean all
	$(MAKE) $@ -C ./libft
