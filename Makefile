NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS+ = -lreadline

SRC =	ft_split.c    \
		test.c    \
		utils_ms.c

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