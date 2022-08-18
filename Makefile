VRLIBFT= libft/libft.a
MANDATORY= main.c builtins.c $(VRLIBFT)

CC=cc
FLAGS= -Wall -Werror -Wextra
DEBUG=-fsanitize=address -g
NAME=minishell

O_MANDATORY=$(MANDATORY:%.c=%.o)
O_BONUS=$(BONUS:%.c=%.o)

all: $(VRLIBFT) $(NAME)

$(VRLIBFT):
	make re -C	libft

$(NAME):
	gcc $(FLAGS) $(MANDATORY) -o $(NAME)

debug:
	gcc $(FLAGS) $(DEBUG) $(MANDATORY) -o $(NAME)

clean:
	rm -rf *.o

fclean:
	rm -rf *.o $(NAME)

re: fclean all
