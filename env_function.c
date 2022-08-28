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
	key = malloc(len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = env[i];
		i++;
	}
	key[len] = '\0';
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
		printf("%s=%s\n", tmp->key, tmp->cont);
		tmp = tmp->next;
	}
	printf("%s%s\n", tmp->key, tmp->cont);
}

t_env_list	*clean_arv(t_env_list *env, t_env_list *new, t_data *data)
{
	t_env_list *t_new;
	t_env_list *tmp;
	t_env_list *result;

	t_new = new;
	result= NULL;
	while (t_new)
	{
		if (check_valid_enva_jout(t_new) == 1)
			printf("%s : not a valid identifier\n", t_new->key);
		else if (check_valid_enva_jout(t_new) == 2 || check_valid_enva_jout(t_new) == 0)
		{
			tmp = malloc(sizeof(t_env_list));
			if (check_valid_enva_jout(t_new) == 0)
			{
				tmp->key = t_new->key;
				tmp->cont = t_new->cont;
				tmp->next = NULL;
			}
			else
			{
				if (doubl_export(data->head_env, t_new) == NULL)
				{
					if (doubl_export(result, t_new) == NULL)
						tmp->cont = t_new->cont;
					else
						tmp->cont = doubl_export(result, t_new);
				}
				else
					tmp->cont = doubl_export(data->head_env, t_new);
				tmp->key = ft_strndup(t_new->key, (ft_strlen(t_new->key) - 1));	
				tmp->next = NULL;
			}
			lstadd_back(&result, tmp);
		}
		if (t_new->next)
			t_new = t_new->next;
		else
			break;
	}
	return result;
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
		lstadd_back(&data->head, tmp);
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
