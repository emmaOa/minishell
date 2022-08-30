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
	t_env_list	*env;
	t_env_list	*arv;
	t_env_list	*tmp;

	env = data->head_env;
	arv = data->arv_list;
	if(env)
	{
		while (env)
		{
			if (ft_strcmp(new->key, env->key) == 0)
			{
				printf("env == 0");
				check_dele(data->head_env, env);
			}
			env = env->next;
		}
	}
	if (arv)
	{
		while (ft_strcmp(arv->key, new->key) != 0)
			arv = arv->next;
		if (arv)
		{
			new->cont = arv->cont;
			check_dele(data->arv_list, arv);
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
				new->cont = ft_strjoin(env->cont, new->cont);
				check_dele(data->head_env, env);
				break;
			}
			env = env->next;
		}
	}
	if (arv)
	{
		while (ft_strcmp(arv->key, new->key) != 0)
			arv = arv->next;
		if (arv)
		{
			new->cont = ft_strjoin(arv->cont, new->cont);
			check_dele(data->arv_list, arv);
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
	// printf("%s\n", data->arv_list->key);
	// exit(0);
	 if (ret == 2)
		remplace_double_2(data, new);
	
	return (0);
}

int	ft_export_arv(t_data *data)
{
	t_env_list	*arv;
	t_env_list	*tmp;

	arv = data->arv_list;
	data->arv_list = arv->next->next;
	dele_node(arv->next);
	dele_node(arv);
	lstadd_back_export(data);
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
