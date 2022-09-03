#include "minishell.h"

int	check_valid_enva_jout(char *str)
{
	int i;

	i = 1;
	if ((!ft_isalpha(str[0]) && str[0] != '_'))
	{
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
	t_env_list *without_equals;

	alpha = 'A';
	env = data->head_env;
	without_equals = data->key_without_cont;
	if (data->ac == 2)
	{
		if (ft_strncmp("export", data->av[1], ft_strlen(data->av[1])) == 0)
		{
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
			prin_if(data->head_env, data->key_without_cont);
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
		prin_if(data->head_env, data->key_without_cont);
		
	}
	return (0);
}
