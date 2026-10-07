NAME = libftprintf.a
CC = cc
CFLAGS= -Wall -Werror -Wextra

SOURCES= ft_printf.c ft_putstr_fd.c ft_putnbr_fd.c	ft_putnbrhexa.c ft_putchar_fd.c ft_putunbr.c

OBJ = $(SOURCES:.c=.o)
BONUS_OBJ = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all 

.PHONY: all bonus clean fclean re
