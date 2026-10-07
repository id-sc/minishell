NAME = minishell

INC_DIR     = includes/
LIBFT_DIR   = libft_muti/
PRINTF_DIR  = printf/
OBJS_DIR    = OBJS/

SRCS	=	source/builtins.c			\
			source/cd.c					\
			source/cleanup.c			\
			source/count.c				\
			source/echo.c				\
			source/env.c				\
			source/executor.c			\
			source/minishell4.c			\
			source/exit.c				\
			source/export.c				\
			source/free.c				\
			source/get_env.c			\
			source/get_path.c 			\
			source/heredoc_quotes.c		\
			source/heredoc.c			\
			source/heredoc_fork.c		\
			source/minishell.c			\
			source/pipeline.c			\
			source/pwd.c				\
			source/redirection.c		\
			source/redirection_exec.c	\
			source/signal.c				\
			source/tokenization.c		\
			source/tokenization2.c		\
			source/tokenization3.c		\
			source/tokenization4.c		\
			source/unset.c				\
			source/utils.c				\
			source/var.c				\
			source/minishell2.c			\
			source/minishell3.c			\
			source/heredoc_utils.c		\
			source/export2.c			\


CC = cc
CFLAGS = -Wall -g3 -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

LIBFT   = $(LIBFT_DIR)libft.a
PRINTF  = $(PRINTF_DIR)libftprintf.a

OBJS    = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(OBJS) $(LIBFT) $(PRINTF) $(LDFLAGS) -no-pie -o $(NAME)

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) 

$(PRINTF):
	@make -C $(PRINTF_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(PRINTF_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re