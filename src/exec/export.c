#include"../../include/minishell.h"

int	check_valid_enva_jout(char *str)
{
	int i;

	i = 1;
	if ((!ft_isalpha(str[0]) && str[0] != '_'))
		return (1);
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


int	ft_export_arv(t_exec_data *data)
{
	t_env_list	*arv;

	arv = data->arv_list;
	data->arv_list = arv->next;
	dele_node(arv);
	lstadd_back_export(data);
	return (0);
}

int	ft_export(t_exec_data *data)
{
	int	alpha;
	t_env_list *env;

	alpha = 'A';
	env = data->head_env;
	if (data->nb_arv == 1)
	{
		env = data->head_env;
		while (alpha <= 'Z')
		{
			while (env)
			{
				if (env->key[0] == alpha)
				{
					if (env->cont)
						printf("declare -x %s=\"%s\"\n", env->key, env->cont);
					else
						printf("declare -x %s\n", env->key);
				}
				env = env->next;
			}
			env = data->head_env;
			alpha++;
		}
		while (env)
		{
			if (env->key[0] < 'A' || env->key[0] > 'Z')
			{
				if (env->cont)
					printf("declare -x %s=\"%s\"\n", env->key, env->cont);
				else
					printf("declare -x %s\n", env->key);
			}
			env = env->next;
		}
	}
	else
	{
		ft_export_arv(data);
		lstadd_back_plus(&data->head_env, data->key_without_cont);
	}
	return (0);
}
