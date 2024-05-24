NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS+ = -lreadline

SRC =	ft_split.c    \
		main.c    \
		utils_ms.c \
		Builtin.c \
		utils_ms2.c \
		ft_split2.c \
		parse.c \
		free_all.c

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(CFLAGS+)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(CFLAGS+)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all