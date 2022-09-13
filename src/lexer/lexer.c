#include"../../include/minishell.h"

t_lexer *init_lexer(char *line)
{
    t_lexer *lexer;
    
    lexer = ft_calloc(1, sizeof(t_lexer));
    lexer->line = line;
    lexer->len_line = ft_strlen(line);
    lexer->i = 0;
    lexer->j = 0;
    lexer->c = line[lexer->i];
    return(lexer);
}

void lexer_advance(t_lexer *lexer)
{
    if(lexer->i < lexer->len_line && lexer->c != '\0')
    {
        lexer->i++;
        lexer->c = lexer->line[lexer->i];
        printf("1:  %c\n", lexer->c);
        // printf("2:  %c\n", lexer->line[lexer->i + 2]);
        // printf("3:  %c\n", lexer->line[lexer->i + 3]);
        // printf("-------\n");
    }
    if (lexer->i+1 < lexer->len_line && lexer->c != '\0')
    {
        lexer->cp = lexer->line[lexer->i+2];
    }
    else
        lexer->cp = '\0';
    if (lexer->i+2 < lexer->len_line && lexer->c != '\0')
    {
        lexer->cpp = lexer->line[lexer->i+3];

    }
    else
        lexer->cpp = '\0';
    printf("-------\n");
    if (lexer->c != '<' && lexer->cp == '<' && lexer->cpp == '<')
    {
        printf("jjj\n");
        lexer->here_doc = 2;
    }
}

t_token *get_next_token(t_lexer *lexer)
{
    lexer->here_doc = 0;
    while (lexer->c != '\0')
    {
            lexer_skip_whitespaces(lexer);
            if (is_a_special_char(lexer))
            {
                lexer_advance(lexer);
                return(fill_token(lexer));
            }
            else
                return(arg_token(lexer));
            lexer_advance(lexer);
    }
    return (NULL);
}