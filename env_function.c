#include "minishell.h"
char *key_evn(char *env)
{
	int	i;
	int	len;
	char *key;

	i = 0;
	while (env[i] != '=')
		i++;
	if (env[i] == '\0')
		return (NULL);
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
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] != '=' || env[i + 1] == '\0')
		cont[j] = '\0';
	else
	{
		i++;
		while (env[i])
		{
			cont[j] = env[i];
			i++;
			j++;
		}
		cont[j] = '\0';
	}
	return cont;
}

void	printf_list_env(t_env_list *list)
{
	t_env_list *tmp;
	tmp = list;
	while (tmp->next)
	{
		printf("%s%s\n", tmp->key, tmp->cont);
		tmp = tmp->next;
	}
	printf("%s%s\n", tmp->key, tmp->cont);
}

t_env_list	*arr_to_list(t_data *data, char *str[])
{
	t_env_list *tmp;
	int i;

	i = 0;
	data->head = NULL;
	while (str[i])
	{
		tmp = malloc(sizeof(t_env_list));
		tmp->key = key_evn(str[i]);
		tmp->cont = cont_evn(str[i]);
		tmp->next = NULL;
		ft_lstadd_back_mini(&data->head, tmp);
		i++;
	}
	return data->head;
}

int	list_to_arr(t_data *data)
{
	int i;

	i = 0;
	t_env_list *tmp;
	tmp = data->head_env;
	data->ev = (char **)malloc(ft_lstsize_mini(data->head_env) * sizeof(char *));
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
