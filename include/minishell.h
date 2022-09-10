/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:51:19 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/31 13:47:59 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
# include <sys/time.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <signal.h>

int v_error;

typedef struct s_token
{
    char *value;
    enum
    {
        ARG,
        R_REDIRECTION = '>',
        L_REDIRECTION = '<',
        PIPE = '|',
    } type;
    
}        t_token;

typedef struct t_lexer
{
    char *line;
    size_t len_line;
    char c;
    unsigned int i;
	unsigned int j;
}       t_lexer;

typedef struct s_data
{
    char 	**args;
    int 	error;
	char	*inf;
	int 	*infiles;
	int 	n_infiles;
	char	**outfiles;
	char 	**append;
    char    **envp;
}       t_data;



typedef struct s_env_list
{
	char	*key;
	char	*cont;
	struct s_env_list *next;
}			t_env_list;

typedef struct s_exec_data
{
   char   *name_built;
   char   *pwd;
   int    nb_arv;
   struct s_env_list *head_env;
   struct s_env_list *env_list;
   struct s_env_list *key_without_cont;
   struct s_env_list *arv_list;
   struct s_env_list *head;
   struct s_env_list *arv_unset;
   struct s_data *parse;
}               t_exec_data;


t_lexer	*init_lexer(char *line);
void	lexer_advance(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
t_token	*init_token(char *value,int type);
t_token	*fill_token(t_lexer *lexer);
int		get_type(char *value);
int		is_a_special_char(char c);
int 	parse(char *line, char **envp, t_exec_data *e_data);
int		ft_strcmp(char *s1, char *s2);
int		ft_strequ(char *s1, char *s2);
void	lexer_skip_whitespaces(t_lexer *lexer);
t_token	*arg_token(t_lexer *lexer);
void	run_qouate(t_lexer *lexer,char *c);
void    free_token(t_token *token);
t_list	*init_execution(char **envp);
t_data	*init_data(char **envp);
int		check_qaout(char *s);
void	single_quote(char *value,char **arg,int i);
int		position_quote_s(char *s,int f);
int		position_quote_d(char *s, int f);
void	double_quote(t_list *exec,char *value,char **arg,int i);
void	qaout(t_list *exec, char *value, char **arg, int i);
int		position_quote(char *s, int f);
void    fill_args(t_list *exec,t_token *token);
void	**ft_2d_realloc(void **arg,int size);
int		len_2d_array(void **array);
void	fill_pipe(t_list *exec, char **envp);
void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer);
void	fill_infile(t_list *exec, t_token *token);
int		*ft_int_realloc(int *ptr, int size);
void	fill_outfile(t_list *exec, t_token *token);
void	fill_append(t_list *exec, t_token *token);
int		handle_errors(char *argv);
int 	check_if_expand(char *s);
void	expand(t_list *exec,char *value,char **arg);
char	*fill_expand(t_list *exec,char *value);
void	expand_split(t_list *exec,char *arg);
int	    count_args(char **args);
char    **create_envp(char **envp);
//-----------------------------------------------------

t_exec_data	*is_builtins(t_list *exec, t_exec_data *e_data);
t_env_list	*arv_to_list(t_exec_data *data, char *str[]);
t_env_list	*arr_to_list(t_exec_data *data, char *str[]);
int         exec_builtins(t_list *exec, t_exec_data *e_data);
int	        ft_echo(char **arv);
int	        ft_check_n_echo(char *str);
int	        nb_arv(char **str);
int	        ft_pwd(void);
char        *key_evn(char *env);
char        *cont_evn(char *env);
int	        printf_list(t_env_list *list);
void	    printf_list_expo(t_env_list *list);
int         just_equals(t_env_list *t_env, t_env_list *node);
int	        plus_equals(t_env_list *t_env, t_env_list *node);
int	        check_equal(char *str, int indec);
int	        check_valid_enva_jout(char *str);
void	    dele_node(t_env_list *node);
void	    lstadd_back_export(t_exec_data *data);
int	        prin_if(t_env_list *t_env, t_env_list *t_without_key);
char        *ft_strndup(char *str, int len);
void    	lstadd_back(t_env_list **lst, t_env_list *new);
int	        ft_export(t_exec_data *data);
int     	ft_export_arv(t_exec_data *data);
void    	lstadd_back_plus(t_env_list **lst, t_env_list *new);
int        	check_unset(char *str);
int         ft_env(t_exec_data *data);
int     	ft_unset(t_exec_data *data);
void	    arv_unset(t_exec_data *data, char *str[]);
int         ft_cd(t_list *exec, t_exec_data *e_data);
char        *check_home(t_list *exec);

#endif