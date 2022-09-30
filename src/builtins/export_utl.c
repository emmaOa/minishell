#include"../../include/minishell.h"

int	just_equals(t_env_list *t_env, t_env_list *node)
{
	t_env_list	*env;

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
	t_env_list	*env;

	env = t_env;
	while (env)
	{
		if (ft_strncmp(env->key, node->key, ft_strlen(env->key)) == 0)
		{
			env->cont = ft_strjoin(ft_strdup(env->cont), node->cont);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	printf_list_expo(t_env_list *list)
{
	t_env_list	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("declare -x %s%s\n", tmp->key, tmp->cont);
		tmp = tmp->next;
	}
}

int	check_equal(char *str, int indec)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || indec < 1)
			return (1);
		i++;
	}
	return (0);
}

int	prin_if(t_env_list *t_env, t_env_list *t_without_key)
{
	int			i;
	t_env_list	*env;
	t_env_list	*without_key;

	env = t_env;
	without_key = t_without_key;
	i = 0;
	while (without_key)
	{
		while (env)
		{
			if (ft_strncmp
				(env->key, without_key->key, ft_strlen(without_key->key)) == 0)
				i = 1;
			env = env->next;
		}
		if (i == 0)
			printf("declare -x %s\n", without_key->key);
		without_key = without_key->next;
	}
	return (0);
}
