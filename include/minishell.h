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

# include	<unistd.h>
# include	<errno.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<string.h>
# include	<sys/wait.h>
# include	<dirent.h>
# include	<ctype.h>
# include	<sys/types.h>
# include	<sys/time.h>
# include	<sys/stat.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"../libft/libft.h"
# include	<fcntl.h>
# include	<signal.h>

typedef struct s_glob
{
	struct s_env_list *head_env;
	int		g_exit_status;
	int		child;
	int		fd_built;
}				t_glob;
t_glob			g_glob;

typedef struct s_token
{
	char	*value;
	enum
	{
		ARG,
		R_REDIRECTION = '>',
		L_REDIRECTION = '<',
		PIPE = '|',
	}			e_type;
}				t_token;

typedef struct t_lexer
{
	char			*line;
	size_t			len_line;
	char			c;
	unsigned int	i;
	unsigned int	j;
}				t_lexer;

typedef struct s_env_list
{
	char	*key;
	char	*cont;
	struct s_env_list *next;
}			t_env_list;

typedef struct s_data
{
	char	**args;
	int		error;
	int		if_hd;
	char	*inf;
	int		*infiles;
    int     len_infiles;
	int		n_infiles;
	char	**outfiles;
	char	**append;
	char	**hd;
}				t_data;

typedef struct s_exec_data
{
   char   *name_built;
   char   *pwd;
   int    nb_arv;
   int    nb_node;
   int    **fd_pipe;
   int	  *fd_her;
   int    fd_outfiles;
   int    forck;
   char   *url;
   int    i;
   int    infile;
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
t_token	*init_token(char *value, int type);
t_token	*fill_token(t_lexer *lexer);
int		get_type(char *value);
int		is_a_special_char(char c);
int	    parse(char *line, t_exec_data *e_data);
int		ft_strcmp(char *s1, char *s2);
int		ft_strequ(char *s1, char *s2);
void	lexer_skip_whitespaces(t_lexer *lexer);
t_token	*arg_token(t_lexer *lexer);
void	run_qouate(t_lexer *lexer, char *c);
void	free_token(t_token *token);
t_list	*init_execution(void);
void	utils1_qaout(t_list *exec, char **tmp, char **arg);
void	utils1_position_quote(int f, int *i, int *q, char *tmp);
int		utils2_position_quote(int j, int *i, int *q, char *tmp);
int		utils3_position_quote(int j, int *i, int *q, char *tmp);
void	utils3_qaout_in_redi(char **tmp, char **arg, t_list *exec);
void	utils2_qaout_in_redi(char **tmp, char **arg, t_list *exec);
void	utils_expand(t_list *exec, char *value, char **tmp, int *i);
void	skip_in_qaout(char *argv, int *i);
t_data	*init_data(void);
int		check_qaout(char *s);
void	single_quote(char *value, char **arg, int i);
int		position_quote_s(char *s, int f);
int		position_quote_d(char *s, int f);
void	double_quote(t_list *exec, char *value, char **arg, int i);
void	qaout(t_list *exec, char *value, char **arg, int i);
int		position_quote(char *s, int f);
void	fill_args(t_list *exec, t_token *token);
void	**ft_2d_realloc(void **arg, int size);
int		len_2d_array(void **array);
void	fill_pipe(t_list *exec);
void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer);
void	fill_infile(t_list *exec, t_token *token);
int		*ft_int_realloc(int *ptr, int size);
void	fill_outfile(t_list *exec, t_token *token);
void	fill_append(t_list *exec, t_token *token);
int		handle_errors(char *argv);
int		check_if_expand(char *s);
void	expand(t_list *exec, char *value, char **arg);
char	*fill_expand(t_list *exec, char *value);
void	expand_split(t_list *exec, char *arg, int f);
void	expand_exit_status(char **tmp, int *i);
void	qaout_in_redi(t_token *token, t_list *exec, char **arg, int i);
void	utils4_qaout_in_redi(char **tmp, char **value);
void	parse_arg_redi(t_token *token, t_list *exec);
void	free_exec(t_list *exec);
int		ft_skip_whitespace(char *av, int *i);
int		red_error(int *i, int *j, char *argv);
char	quotes_exist(char *argv, size_t *i);
int		handle_quotes(char *s);
int		ft_cmp(char *s, char c);
void	utils_handle_errors(char *argv, size_t *i, size_t *j);
char	*ft_join(char *s1, char *s2);
char	*get_variable_name(char *str);
int		get_char_index(char *str, char c);
int		is_acceptable(char c);
int		big_len(int s1, int s2);
char	**create_envp(char **envp);
int		count_args(char **args);
void	free_2d_array(char **arr);
char	**add_env(char **strs, char *arg);

//-----------------------------------------------------

t_exec_data	*is_builtins(t_list *exec, t_exec_data *e_data);
t_env_list	*arv_to_list(t_exec_data *data, char *str[]);
t_env_list	*ft_lstlast_mini(t_env_list *lst);
int			ft_lstsize_mini(t_env_list *lst);
void        arr_to_list(t_exec_data *data, char *str[]);
int         exec_builtins(t_list *exec, t_exec_data *e_data);
int	        ft_echo(char **arv);
int	        ft_check_n_echo(char *str);
int	        nb_arv(char **str);
int	        ft_pwd(t_exec_data *e_data);
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
char        *check_home(t_exec_data *e_data);
char        *val_env(char **env);
int         check_trash(char *buf);
void		here_d(char *delimiter, t_exec_data *e_data, int len);
void        exec_cmd(t_list *exec, t_exec_data *e_data);
int     	ft_pipe(t_exec_data *e_data);
void    	ft_exit_bonus(char *s);
int     	ft_open_outfiles(t_exec_data *e_data, t_list *exec);
int     	mult_pipe(t_exec_data *e_data, t_list *exec);
void    	ft_foork(t_exec_data *e_data);
void    	ft_close(t_exec_data *data);
char    	*ft_path(char *env[]);
int     	ft_len_2d(char **tabl);
char    	*ft_url(char *path, t_list *exec);
void    	ft_wait(t_exec_data *e_data);
void    	ft_free_int(int **tabl, int start, int len);
void    	free_bonus_int(int **tabl, int start, int len);
void        sig_handler(int signum);
void        sig_handler_child(int signum);
int     	check_inf(int *infiles, int len, int nb_node, t_exec_data *e_data);
int			exec_herdoc(t_list *exec, t_exec_data *e_data);
void		sig_main(void);
void		sig_child(void);
void		exec_builtins_utl(t_list *exec, t_exec_data *e_data, char **arv);
void		val_env_utl(char *val, char **env, int i);
int			ft_unset_utl(t_exec_data *data, char *key);
void		cd_utl(t_exec_data *e_data, char **arv);
void		my_pwd(t_exec_data *e_data, char **arv);
void		with_alpha(t_exec_data *data);
void		without_alpha(t_exec_data *data);
void		without_cont(t_exec_data *data, char *str);
void		not_str(t_exec_data *data);
void		with_cont(t_exec_data *data, char *str);
void		end_foork(t_exec_data *e_data);
void		start_foork(t_exec_data *e_data);
void		middle_foork(t_exec_data *e_data);
char		*check_home_utl(int i, t_exec_data *e_data);
void		add_back_plus_equal(t_exec_data *data, char *cont, char *key);
void		add_back_equal(t_exec_data *data, char *cont, char *key);
void 		ft_p(char **str);
char	 	**list_to_arr(t_env_list *env);
int			mult_cmd(t_exec_data *e_data, t_list *exec);
int			out_file(t_exec_data *e_data, t_list *exec);
int			execution(t_exec_data *e_data, t_list *exec);
char		*random_name(void);
int			list(t_exec_data *e_data, t_list *exec);

#endif