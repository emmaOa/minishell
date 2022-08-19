VRLIBFT= libft/libft.a
MANDATORY= main.c builtins.c $(VRLIBFT)

CC=cc
FLAGS= #-Wall -Werror -Wextra
DEBUG=-fsanitize=address -g
NAME=minishell

O_MANDATORY=$(MANDATORY:%.c=%.o)
O_BONUS=$(BONUS:%.c=%.o)

all: $(NAME)

$(VRLIBFT):
	make bonus -C	libft

$(NAME):$(VRLIBFT)
	gcc $(FLAGS) $(MANDATORY) -o $(NAME)

debug:$(VRLIBFT)
	gcc $(FLAGS) $(DEBUG) $(MANDATORY) -o $(NAME)

clean:
	make clean -C libft
	rm -rf *.o

fclean:
	make fclean -C libft
	rm -rf *.o $(NAME)

re: fclean all
