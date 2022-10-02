#include "../../include/minishell.h"

int	nb_arv(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char *ft_strndup(char *str, int len)
{
	char *c;
	int  i;

	i = 0;
	c = ft_calloc(len + 1, sizeof(char));
	if (!c)
		return (NULL);
	while (i < len)
	{
		c[i] = str[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

void	dele_node(t_env_list *node)
{
	if (!node)
		return ;
	node->cont = NULL;
	node->key = NULL;
	free(node);
	return ;
}

char 	**list_to_arr(t_exec_data *data)
{
	int i;

	i = 0;
	t_env_list *tmp;
	tmp = data->head_env;
	free_2d_array(data->ev);
	data->ev = (char **)malloc(ft_lstsize_mini(data->head_env) * sizeof(char *));
	while (tmp->next)
	{
		if (tmp->cont)
		{
			data->ev[i] = ft_strjoin(ft_strdup(tmp->key), "=");
			data->ev[i] = ft_strjoin(data->ev[i], tmp->cont);
		}
		tmp = tmp->next;
		i++;
	}
	data->ev[i] = NULL;
	return (data->ev);
}
