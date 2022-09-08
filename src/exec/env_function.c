#include"../../include/minishell.h"
char *key_evn(char *str)
{
	int	i;
	int	len;
	char *key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	len = i;
	key = malloc(len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = str[i];
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

t_env_list	*arv_to_list(t_exec_data *data, char *str[])
{
	t_env_list *tmp1;
	t_env_list *tmp2;
	int i;

	i = 0;
	data->head = NULL;
	data->key_without_cont = NULL;
	while (str[i])
	{
		if (check_equal(str[i], i) == 1)
		{
			tmp1 = malloc(sizeof(t_env_list));
			tmp1->key = key_evn(str[i]);
			tmp1->cont = cont_evn(str[i]);
			tmp1->next = NULL;
			lstadd_back(&data->head, tmp1);
		}
		else if (check_equal(str[i], i) == 0)
		{
			if (check_valid_enva_jout(str[i]) == 0)
			{
				tmp2 = malloc(sizeof(t_env_list));
				tmp2->key = str[i];
				tmp2->cont = NULL;
				tmp2->next = NULL;
				lstadd_back(&data->key_without_cont, tmp2);
			}
			else
				printf("%s : not a valid identifier\n", str[i]);
		}
		i++;
	}
	return data->head;
}

int	printf_list(t_env_list *list)
{
	t_env_list *tmp;
	tmp = list;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->cont);
		tmp = tmp->next;
	}
	return (0);
}

void	printf_list_expo(t_env_list *list)
{
	t_env_list *tmp;
	tmp = list;
	while (tmp)
	{
		printf("declare -x %s%s\n", tmp->key, tmp->cont);
		tmp = tmp->next;
	}
}

int just_equals(t_env_list *t_env, t_env_list *node)
{
	t_env_list *env;

	env = t_env;
	while (env)
	{
		if (ft_strcmp(env->key, node->key) == 0)
		{
			env->cont = node->cont;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	plus_equals(t_env_list *t_env, t_env_list *node)
{
	t_env_list *env;

	env = t_env;
	while (env)
	{
		if (ft_strncmp(env->key, node->key, ft_strlen(env->key)) == 0)
		{
			env->cont = ft_strjoin(env->cont, node->cont);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

t_env_list	*arr_to_list(t_exec_data *data, char *str[])
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

int	check_equal(char *str, int indec)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || indec < 1)
			return 1;
		i++;
	}
	return 0;
}



int	prin_if(t_env_list *t_env, t_env_list *t_without_key)
{
	t_env_list *env;
	t_env_list *without_key;
	int i;

	env = t_env;
	without_key = t_without_key;
	i = 0;

	while (without_key)
	{
		while (env)
		{
			if (ft_strncmp(env->key, without_key->key, ft_strlen(without_key->key)) == 0)
				i = 1;
			env = env->next;
		}
		if (i == 0)
			printf("declare -x %s\n", without_key->key);
		without_key = without_key->next;
	}
	return (0);
}

// int	list_to_arr(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	t_env_list *tmp;
// 	tmp = data->head_env;
// 	data->ev = (char **)malloc(ft_lstsize_mini(data->head_env) * sizeof(char *));
// 	while (tmp->next)
// 	{
// 		data->ev[i] = (char *)malloc((ft_strlen(tmp->cont) + ft_strlen(tmp->key) + 1));
// 		data->ev[i] = ft_strjoin(tmp->key, tmp->cont);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	data->ev[i] = NULL;
// 	return (0);
// }

void	arv_unset(t_exec_data *data, char *str[])
{
	t_env_list *tmp;
	int i;

	i = 0;
	data->arv_unset = NULL;
	while (str[i])
	{
		tmp = malloc(sizeof(t_env_list));
		tmp->key = str[i];
		tmp->cont = "\0";
		tmp->next = NULL;
		lstadd_back(&data->arv_unset, tmp);
		i++;
	}
	return ;
}

