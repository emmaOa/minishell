#include "minishell.h"

int	check_valid_enva_jout(t_env_list *node)
{
	int i;

	i = 1;
	if (!ft_isalpha(node->key[0]) && node->key[0] != '_')
		return (1);
	while (node->key[i])
	{
		if (!ft_isalpha(node->key[0]) && !ft_isalnum(node->key[0]) && node->key[0] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export_arv(t_data *data)
{
	t_env_list *tmp;

	int i = 0;
	tmp = data->arv_list;

	while (ft_strncmp("export", tmp->key, ft_strlen(tmp->key)) != 0)
		tmp = tmp->next;
	tmp = tmp->next;
	ft_lstadd_back_mini(&data->head_env, tmp);
	tmp = data->head_env;
	// printf_list_env(tmp);
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
						printf("declare -x %s\"%s\"\n", env->key, env->cont);
					env = env->next;
				}
				env = data->head_env;
				alpha++;
			}
			while (env->next)
			{
				if (env->key[0] < 'A' || env->key[0] > 'Z')
					printf("declare -x %s\"%s\"\n", env->key, env->cont);
				env = env->next;
			}
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
					printf("declare -x %s\"%s\"\n", env->key, env->cont);
				env = env->next;
			}
			env = data->head_env;
			alpha++;
		}
		while (env->next)
		{
			if (env->key[0] < 'A' || env->key[0] > 'Z')
				printf("declare -x %s\"%s\"\n", env->key, env->cont);
			env = env->next;
		}
		printf("declare -x %s\"%s\"\n", env->key, env->cont);
	}
	return (0);
}
