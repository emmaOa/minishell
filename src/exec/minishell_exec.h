#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <time.h>
 #include <string.h>
# include "libft/libft.h"
# include <sys/time.h>
# include <stdlib.h>
#include <fcntl.h>

typedef struct s_env_list
{
	char	*key;
	char	*cont;
	struct s_env_list *next;
}			t_env_list;

typedef struct s_data
{
	int			ac;
	char		**av;
	int			len_env;
	struct s_env_list *arv_list;
	struct s_env_list *arv_unset;
	struct s_env_list *env_list;
	struct s_env_list *key_without_cont;
	struct s_env_list *head;
	struct s_env_list *head_env;
	char	**ev;
}			t_data;

t_env_list	*arv_to_list(t_data *data, char *str[]);
t_env_list	*arr_to_list(t_data *data, char *str[]);
t_env_list	*ft_lstnew_mini(void *key, void *cont);
t_env_list	*arv_unset(t_data *data, char *str[]);
t_env_list	*ft_lstlast_mini(t_env_list *lst);
char		 *cont_evn(char *env);
char		 *ft_strndup(char *str, int len);
char		 *key_evn(char *env);
void		lstadd_back_export(t_data *data);
void		printf_list_env(t_env_list *list);
void		lstadd_back(t_env_list **lst, t_env_list *new);
void		dele_node(t_env_list *node);
void		check_dele(t_env_list *data, t_env_list *node);
int			check_valid_enva_jout(char *str);
int			ft_lstsize_mini(t_env_list *lst);
int			ft_export_arv(t_data *data);
int			ft_check_n_echo(char *str);
int			list_to_arr(t_data *data);
int			ft_export(t_data *data);
int			ft_echo(t_data *data);
int			ft_pwd(t_data *data);
int			just_equals(t_env_list *t_env, t_env_list *node);
int			plus_equals(t_env_list *t_env, t_env_list *node);
int			ft_strcmp(const char *d, const char *s);
int			prin_if(t_env_list *t_list, t_env_list *node);
int			ft_env(t_data *data);
int			ft_unset(t_data *data);
int			check_unset(char *str);
int			printf_list(t_env_list *list);
#endif