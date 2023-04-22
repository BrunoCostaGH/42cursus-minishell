CC=cc
CFLAGS=-Wall -Werror -Wextra
DEPS=libft/libft.a

SRCS=prompt.c exit.c exec.c exec_utils.c minishell_utils.c pwd.c
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
