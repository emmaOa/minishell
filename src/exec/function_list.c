#include"../../include/minishell.h"

t_env_list	*ft_lstlast_mini(t_env_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	lstadd_back_plus(t_env_list **lst, t_env_list *new)
{
	t_env_list	*tmp;

	if (new == 0)
		return ;
	while (new)
	{
		if (just_equals(*lst, new) == 0)
		{
			tmp = malloc(sizeof(t_env_list));
			tmp->cont = new->cont;
			tmp->key = new->key;
			tmp->next = NULL;
			lstadd_back(lst, tmp);
		}
		new = new->next;
	}
}

void	lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*p;

	if (new == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	p = ft_lstlast_mini(*lst);
	p->next = new;
}

void	lstadd_back_export(t_exec_data *data)
{
	t_env_list	*arv;
	t_env_list	*tmp;

	arv = data->arv_list;
	while (arv)
	{
		if (check_valid_enva_jout(arv->key) == 2)
		{
			if (plus_equals(data->head_env, arv) == 0)
			{
				tmp = malloc(sizeof(t_env_list));
				tmp->key = ft_strndup(arv->key, (ft_strlen(arv->key) - 1));
				tmp->cont = arv->cont;
				tmp->next = NULL;
				lstadd_back(&data->head_env, tmp);
			}
		}
		else if (check_valid_enva_jout(arv->key) == 0)
		{
			if (just_equals(data->head_env, arv) == 0)
			{
				tmp = malloc(sizeof(t_env_list));
				tmp->key = arv->key;
				tmp->cont = arv->cont;
				tmp->next = NULL;
				lstadd_back(&data->head_env, tmp);
			}
		}
		else if (check_valid_enva_jout(arv->key) == 1)
		{
			ft_putstr_fd(arv->key, 2);
			ft_putstr_fd("=", 2);
			ft_putstr_fd(arv->cont, 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
		}
		arv = arv->next;
	}
}

int	ft_lstsize_mini(t_env_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

t_env_list	*ft_lstnew_mini(void *key, void *cont)
{
	t_env_list	*new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->cont = cont;
	new->key = key;
	new->next = NULL;
	return (new);
}

char *check_home(void)
{
	char *path;
	int i;
	int j;
	int x;


	i = 0;
	x = 0;
	while (g_glob.envp[i])
	{
		if (ft_strncmp(g_glob.envp[i], "HOME", ft_strlen("HOME")) == 0)
		{
			path = malloc(ft_strlen(g_glob.envp[i]) - ft_strlen("HOME"));
			j = 0;
			while (g_glob.envp[i][j] != '=')
				j++;
			j++;
			while (g_glob.envp[i][j])
			{
				path[x] = g_glob.envp[i][j];
				x++;
				j++;
			}
			path[x] = '\0';
			return (path);
		}
		i++;
	}
	return (NULL);
}