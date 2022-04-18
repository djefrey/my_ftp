##
## EPITECH PROJECT, 2022
## B-NWP-400-STG-4-1-myftp-jeffrey.winkler
## File description:
## Makefile
##

SRC				=	src/main.c						\
					src/socket.c					\
					src/list.c						\
					src/utils.c						\
					src/client/client.c				\
					src/client/conn.c				\
					src/client/file.c				\
					src/commands/commands.c			\
					src/commands/user.c				\
					src/commands/conn.c				\
					src/commands/files.c			\
					src/commands/working_dir.c		\
					src/commands/utilitaries.c		\
					src/commands/list.c				\
					src/commands/utils.c

OBJ				=	$(SRC:.c=.o)

INC_DIR			=	include

CFLAGS			+=	-Wall -I$(INC_DIR)

NAME			=	myftp

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)

debug: CFLAGS += -g
debug: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
