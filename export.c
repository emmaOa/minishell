#include "minishell.h"

int	check_valid_enva_jout(char *str)
{
	int i;

	i = 1;
	if ((!ft_isalpha(str[0]) && str[0] != '_'))
	{
		
		// exit(0);
		return (1);
	}
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isalnum(str[i]) && str[i] != '_'
			&& (str[i] == '+' && str[i + 1] != '\0'))
			return (1);
		if (str[i] == '+' && str[i + 1] == '\0')
			return (2);
		i++;
	}
	return (0);
}

int	remplace_double_0(t_data *data, t_env_list *new)
{
	t_env_list *env;
	t_env_list *arv;
	int i;

	i = 0;
	env = data->head_env;
	arv = data->arv_list;
	if(env)
	{
		while (env->next)
		{
			if (ft_strcmp(new->key, env->key) == 0)
			{
				env->cont = new->cont;
				dele_node(&data->arv_list, new);
			}
			env = env->next;
		}
	}
	if (arv)
	{
		while (arv->next)
		{
			if (ft_strcmp(new->key, arv->key) == 0)
			{
				arv->cont = new->cont;
				dele_node(&data->arv_list, new);
			}
			arv = arv->next;
		}
	}
	return (0);
}

int	remplace_double_2(t_data *data, t_env_list *new)
{
	t_env_list *env;
	t_env_list *arv;

	env = data->head_env;
	arv = data->arv_list;
	new->key = ft_strndup(new->key, (ft_strlen(new->key) - 1));
	if(env)
	{
		while (env->next)
		{
			if (ft_strcmp(new->key, env->key) == 0)
			{
				env->cont = ft_strjoin(env->cont, new->cont);
				dele_node(&data->arv_list, new);
			}
			env = env->next;
		}
	}
	if (arv)
	{
		while (arv->next)
		{
			printf("%s\n", arv->key);
			if (ft_strcmp(new->key, arv->key) == 0)
			{
				arv->cont = ft_strjoin(arv->cont, new->cont);
				dele_node(&data->arv_list, new);
			}
			arv = arv->next; 
		}
	}
	return (0);
}

int	remplace_double(t_data *data, t_env_list *new, int ret)
{
	t_env_list *arv;

	arv = data->arv_list;
	if (ret == 0)
		remplace_double_0(data, new);
	else if (ret == 2)
		remplace_double_2(data, new);
	return (0);
}

char *doubl_export(t_env_list *list, t_env_list *node)
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

int	ft_export_arv(t_data *data)
{
	t_env_list *tmp;
	t_env_list *clean;

	tmp = data->arv_list;

	if (tmp)
	{
		while (tmp->next && ft_strcmp("export", tmp->key) != 0)
		{
			dele_node(&data->arv_list, tmp);
			tmp = tmp->next;
		}
		dele_node(&data->arv_list, tmp);
		lstadd_back_export(data);
	}
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
			lstadd_back(&env, data->key_without_cont);
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
		printf_list_env(data->key_without_cont);
	}
	return (0);
}
