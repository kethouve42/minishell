

NAME = minishell_version_table
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS+ = -lreadline

SRC = use.c	\
	use2.c	\
	pipex.c	\
	Builtin.c	\
	Builtin2.c	\
	free_all.c	\
	ft_split.c	\
	ft_split2.c	\
	table.c	\
	parse.c	\
	pipex2.c	\
	utils_ms.c	\
	utils_ms2.c	\
	utils_ms3.c	\
	exec.c	\
	exec2.c	\
	cmd.c	\
	ft_itoa.c \
	signal.c \
	absolute.c \
	pipex_no.c	\
	pipex2_no.c	\
	paste_var.c \

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

re: fclean all
