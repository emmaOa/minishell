#include "minishell.h"

char *key_evn(char *env)
{
	int	i;
	int	len;
	char *key;

	i = 0;
	while (env[i] != '=')
		i++;
	len = i;
	key = malloc(len + 2);
	i = 0;
	while (i < len)
	{
		key[i] = env[i];
		i++;
	}
	key[len] = '=';
	key[len + 1] = '\0';
	return (key);
	
}

char *cont_evn(char *env)
{
	int i;
	int j;
	char *cont;

	i = 0;
	j = 0;
	cont = malloc(ft_strlen(env));
	while (env[i] != '=')
		i++;
	i++;
	while (env[i])
	{
		cont[j] = env[i];
		i++;
		j++;
	}
	cont[j] = '\0';
	return cont;
}

void	printf_list_env(t_env_list **list)
{
	t_env_list *first_node;
	first_node = *list;
	while (first_node->next)
	{
		printf("%s%s\n", first_node->key, first_node->cont);
		first_node = first_node->next;
	}
}

t_env_list	**arr_to_list(t_data *data, char *env[])
{
	int i;

	i = 0;
	data->head = (t_env_list **)malloc(sizeof(t_env_list *));
	data->env_list = (t_env_list *)malloc(sizeof(t_env_list));
	data->len_env = 1;
	*data->head = data->env_list;
	while (env[i])
	{
		data->env_list->key = key_evn(env[i]);
		data->env_list->cont = cont_evn(env[i]);
		data->env_list->next = (t_env_list *)malloc(sizeof(t_env_list));
		data->env_list = data->env_list->next;
		data->len_env++;
		i++;
	}
	data->env_list->next = NULL;
	return data->head;
}

int	list_to_arr(t_data *data)
{
	int i;

	i = 0;
	t_env_list *tmp;
	tmp = *data->head;
	data->ev = (char **)malloc(data->len_env * sizeof(char *));
	while (tmp->next)
	{
		data->ev[i] = (char *)malloc((ft_strlen(tmp->cont) + ft_strlen(tmp->key) + 1));
		data->ev[i] = ft_strjoin(tmp->key, tmp->cont);
		tmp = tmp->next;
		i++;
	}
	data->ev[i] = NULL;
	return (0);
}
