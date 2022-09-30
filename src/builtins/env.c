#include"../../include/minishell.h"

void	val_env_utl(char *val, char **env, int i)
{
	int		j;
	int		x;

	j = 0;
	x = 0;
	while (env[i][j] != '=')
		j++;
	while (env[i][++j])
	{
		val[x] = env[i][j];
		x++;
	}
	val[x] = '\0';
}

char	*val_env(char **env)
{
	int		i;
	char	*val;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", ft_strlen("PWD")) == 0)
			val = malloc(ft_strlen(env[i]) + 1);
		i++;
	}
	if (!val)
	{
		val = malloc(ft_strlen("not PWD") + 1);
		val = "not PWD";
	}
	return (val);
}

int	ft_env(t_exec_data *data)
{
	t_env_list	*env;

	env = data->head_env;
	while (env)
	{
		if (env->cont)
			printf("%s=%s\n", env->key, env->cont);
		env = env->next;
	}
	return (0);
}

int	printf_list(t_env_list *list)
{
	t_env_list	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->cont);
		tmp = tmp->next;
	}
	return (0);
}
