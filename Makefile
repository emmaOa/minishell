VRLIBFT= ./libft/libft.a
MANDATORY= src/minishell.c src/lexer/lexer.c src/lexer/token.c src/lexer/lexer_utils.c src/parse/parse.c\
		src/parse/args.c src/parse/init_struct.c src/parse/pipe.c src/parse/redirections.c \
		src/parse/qaout.c  src/parse/expand.c src/parse/expand_utils.c\
		src/parse/envp.c src/errors_handle/handle_errors.c src/errors_handle/handle_errors_utils.c\
		src/builtins/builtins.c src/builtins/check_builtins.c src/builtins/cd.c\
		src/builtins/echo.c src/builtins/env.c src/builtins/export.c src/builtins/export_utl.c\
		src/builtins/pwd.c src/builtins/unset.c src/builtins/put_fd_built.c src/exec/arry_function.c\
		src/exec/foork.c src/exec/url_exec.c src/exec/open_close_wait.c src/exec/pipe.c\
		src/exec/env_function.c src/exec/function_list.c src/exec/function_util.c\
		src/exec/exec_cm.c src/errors_handle/handle_errors_utils1.c src/exec/start_foork.c\
		src/exec/lst_add_back.c src/exec/herdoc.c src/exec/signals.c src/exec/herdoc_utl.c\
		src/exec/exec.c src/exec/list.c  src/exec/initialization.c src/parse/redirection_utils1.c\
		src/parse/free.c src/parse/qaout_utils.c src/parse/redirections_utils.c\
		src/parse/utils.c src/builtins/exit.c $(VRLIBFT)\

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
	make bonus -C ./libft

$(NAME):$(VRLIBFT)
	gcc $(FLAGS) $(MANDATORY) -lreadline $(LFLAGS) $(IFLAGS) -o $(NAME)

debug:$(VRLIBFT)
	gcc $(FLAGS) $(DEBUG) $(MANDATORY) $(VRLIBFT) -lreadline $(LFLAGS) $(IFLAGS) -o $(NAME) 

clean:
	make clean -C libft
	rm -rf *.o

fclean:
	make fclean -C libft
	rm -rf *.o $(NAME)

re: fclean all
