#include "minishell.h"

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

void	dele_node(t_env_list **head, t_env_list *node)
{
	t_env_list *list;
	t_env_list *tmp;
	if (!*head || !node)
		return ;
	while (list->next)
	{
		if (ft_strcmp(list->key, node->key) == 0)
		{
			tmp = list->next;
			list = tmp->next;
			free(tmp);
			tmp = NULL;
		}
	}
	return ;
}

void	lstadd_back_export(t_data *data)
{
	t_env_list	*env;
	t_env_list	*arv;

	env = data->head_env;
	arv = data->arv_list;
	if (arv == 0)
		return ;
	if (env == 0)
	{
		clean_arv(data);
		env = data->arv_list;
		return ;
	}
	env = ft_lstlast_mini(data->head_env);
	clean_arv(data);
	env->next = data->arv_list;
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

