#include"../../include/minishell.h"

char	*check_home(void)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (g_glob.envp[i])
	{
		if (ft_strncmp(g_glob.envp[i], "HOME", ft_strlen("HOME")) == 0)
			return (check_home_utl(i));
		i++;
	}
	return (NULL);
}

char	*check_home_utl(int i)
{
	int		x;
	int		j;
	char	*path;

	x = 0;
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
