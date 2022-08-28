#include "minishell.h"

int	check_valid_enva_jout(t_env_list *node)
{
	int i;

	i = 1;
	if ((!ft_isalpha(node->key[0]) && node->key[0] != '_'))
		return (1);
	while (node->key[i])
	{
		if (!ft_isalpha(node->key[i]) && !ft_isalnum(node->key[i]) && node->key[i] != '_'
			&& (node->key[i] == '+' && node->key[i + 1] != '\0'))
			return (1);
		if (node->key[i] == '+' && node->key[i + 1] == '\0')
			return (2);
		i++;
	}
	return (0);
}

char *	doubl_export(t_env_list *list, t_env_list *node)
{
	t_env_list *tmp;
	char *str;

	tmp = list;
	str = NULL;
	if (list != 0)
	{
		while (tmp->next)
		{
			if (ft_strncmp(tmp->key, node->key, ft_strlen(tmp->key) == 0)
				&& node->key[ft_strlen(tmp->key) + 1] == '\0')
				str = ft_strjoin(tmp->next->cont, node->cont);
			tmp = tmp->next;
		}
	}
	return str;
}

void	lstadd_back_export(t_env_list **lst, t_env_list *new, t_data *data)
{
	t_env_list	*p;
	t_env_list	*tmp;

	tmp = 	NULL;
	if (new == 0)
		return ;
	if (*lst == 0)
	{
		*lst = clean_arv(*lst, new, data);
		return ;
	}
	p = ft_lstlast_mini(*lst);
	p->next = clean_arv(*lst, new, data);
}

int	ft_export_arv(t_data *data)
{
	t_env_list *tmp;
	t_env_list *key;

	// check_key_without_cont(data);
	data->key_without_cont = NULL;	
	tmp = data->arv_list;
	key = data->arv_list;
	while (ft_strncmp("export", tmp->key, ft_strlen(tmp->key)) != 0)
		tmp = tmp->next;
	tmp = tmp->next;
	key = tmp;
	lstadd_back_export(&data->head_env, tmp, data);
	// lstadd_back_export(&data->key_without_cont, key, data);
	return (0);
}

int	ft_export(t_data *data)
{
	int	alpha;
	t_env_list *env;

	alpha = 'A';
	env = data->head_env;
	if (data->ac == 2)
	{
		if (ft_strncmp("export", data->av[1], ft_strlen(data->av[1])) == 0)
		{
			while (alpha <= 'Z')
			{
				while (env->next)
				{
					if (env->key[0] == alpha)
						printf("declare -x %s=\"%s\"\n", env->key, env->cont);
					env = env->next;
				}
				env = data->head_env;
				alpha++;
			}
			while (env->next)
			{
				if (env->key[0] < 'A' || env->key[0] > 'Z')
					printf("declare -x %s=\"%s\"\n", env->key, env->cont);
				env = env->next;
			}
			printf("declare -x %s=\"%s\"\n", env->key, env->cont);
		}
	}
	else
	{
		ft_export_arv(data);
		env = data->head_env;
		while (alpha <= 'Z')
		{
			while (env->next)
			{
				if (env->key[0] == alpha)
					printf("declare -x %s=\"%s\"\n", env->key, env->cont);
				env = env->next;
			}
			env = data->head_env;
			alpha++;
		}
		while (env->next)
		{
			if (env->key[0] < 'A' || env->key[0] > 'Z')
				printf("declare -x %s=\"%s\"\n", env->key, env->cont);
			env = env->next;
		}
		printf("declare -x %s=\"%s\"\n", env->key, env->cont);
	}
	return (0);
}

// void	check_key_without_cont(t_data *data)
// {
// 	t_env_list	*tmp;

// 	tmp = data->arv_list;	
// 	while (ft_strncmp("export", tmp->key, ft_strlen(tmp->key)) != 0)
// 		tmp = tmp->next;
// 	tmp = tmp->next;
// 	exit(0);
// 	// printf("%s\n", tmp->key);
// 	ft_lstadd_back_withoutcont(&data->key_without_cont, tmp);
// 	printf_list_env(data->key_without_cont);
// }
