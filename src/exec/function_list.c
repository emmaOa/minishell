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
	t_env_list	*env;
	t_env_list	*arv;
	t_env_list	*tmp;

	arv = data->arv_list;
	env = data->head_env;
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
			printf("`%s=%s': not a valid identifier\n", arv->key, arv->cont);
		arv = arv->next;
	}
}

// t_env_list	*ft_lstnew_mini(void *key, void *cont)
// {
// 	t_env_list	*new;

// 	new = (t_env_list *)malloc(sizeof(t_env_list));
// 	if (!new)
// 		return (NULL);
// 	new->cont = cont;
// 	new->key = key;
// 	new->next = NULL;
// 	return (new);
// }

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

