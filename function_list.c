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

void	ft_lstadd_back_mini(t_env_list **lst, t_env_list *new)
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

