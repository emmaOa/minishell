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
	struct s_env_list *env_list;
	struct s_env_list *head;
	struct s_env_list *head_env;
	char	**ev;
}			t_data;

t_env_list	*arr_to_list(t_data *data, char *str[]);
t_env_list	*ft_lstnew_mini(void *key, void *cont);
t_env_list	*ft_lstlast_mini(t_env_list *lst);
void		ft_lstadd_back_mini(t_env_list **lst, t_env_list *new);
int			check_valid_enva_jout(t_env_list *node);
void		printf_list_env(t_env_list *list);
int			ft_lstsize_mini(t_env_list *lst);
int			ft_export_arv(t_data *data);
int			ft_check_n_echo(char *str);
int			list_to_arr(t_data *data);
int			ft_export(t_data *data);
char		 *cont_evn(char *env);
int			ft_echo(t_data *data);
char		 *key_evn(char *env);
int			ft_pwd(t_data *data);
#endif