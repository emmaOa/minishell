VRLIBFT= libft/libft.a
MANDATORY= src/minishell.c src/lexer/lexer.c src/lexer/token.c src/lexer/lexer_utils.c src/parse/parse.c\
		src/parse/args.c src/parse/init_struct.c src/parse/pipe.c src/parse/redirections.c \
		src/parse/qaout.c  src/parse/expand.c src/parse/expand_utils.c\
		src/parse/envp.c src/errors_handle/handle_errors.c\
		src/exec/main.c src/exec/builtins.c src/exec/env_function.c src/exec/export.c\
		src/exec/function_list.c src/exec/function_util.c src/exec/check_builtins.c\
		src/exec/cd.c src/exec/exec_cm.c $(VRLIBFT)\

CC=cc
FLAGS= -Wall -Werror -Wextra
DEBUG=-fsanitize=address -g
NAME=minishell

O_MANDATORY=$(MANDATORY:%.c=%.o)
O_BONUS=$(BONUS:%.c=%.o)
LFLAGS = -L ~/.brew/opt/readline/lib

IFLAGS = -I ~/.brew/opt/readline/include

all: $(NAME)

$(VRLIBFT):
	make bonus -C	libft

$(NAME):$(VRLIBFT)
	gcc $(FLAGS) $(MANDATORY) -lreadline $(LFLAGS) $(IFLAGS) -o $(NAME)

debug:$(VRLIBFT)
	gcc $(FLAGS) $(DEBUG) $(MANDATORY) -lreadline $(LFLAGS) $(IFLAGS) -o $(NAME)

clean:
	make clean -C libft
	rm -rf *.o

fclean:
	make fclean -C libft
	rm -rf *.o $(NAME)

re: fclean all
