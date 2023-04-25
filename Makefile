CC=cc
CFLAGS=-Wall -Werror -Wextra
DEPS=libft/libft.a

SRCS=main.c exit.c exec.c pwd.c change_dir.c exec_utils.c minishell_utils.c \
 init.c env.c signals.c exit_status.c
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
