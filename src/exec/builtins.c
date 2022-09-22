#include"../../include/minishell.h"

int	exec_builtins(t_list *exec, t_exec_data *e_data)
{
	char **arv;

	arv = NULL;
	if (((t_data *)exec->content)->args)
	{
		arv = ((t_data *)exec->content)->args;
		if (ft_strncmp(e_data->name_built, "echo", ft_strlen("echo")) == 0)
			ft_echo(arv);
		else if (ft_strncmp(arv[0], "pwd", ft_strlen("pwd")) == 0)
			ft_pwd(e_data);
		else if (ft_strncmp(arv[0], "export", ft_strlen("export")) == 0)
		{
			e_data->arv_list = arv_to_list(e_data, arv);
			ft_export(e_data);
		}
		else if (ft_strncmp(arv[0], "unset", ft_strlen("unset")) == 0)
		{
			arv_unset(e_data, ((t_data *)exec->content)->args);
			ft_unset(e_data);
		}
		else if (ft_strncmp(arv[0], "env", ft_strlen("env")) == 0)
			ft_env(e_data);
		else if (ft_strncmp(arv[0], "exit", ft_strlen("exit")) == 0)
			exit(0);
		if (ft_strncmp(arv[0], "cd", ft_strlen("cd")) == 0)
			ft_cd(exec, e_data);
	}
	if (e_data->nb_node != 1)
		exit(0);
	return (0);
}

char *val_env(char **env)
{
	int i;
	int j;
	int x;
	char *val;

	i = 0;
	j = 0;
	x = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", ft_strlen("PWD")) == 0)
		{
			val = malloc(ft_strlen(env[i]) + 1);
			while (env[i][j] != '=')
				j++;
			while (env[i][++j])
			{
				val[x] = env[i][j];
				x++;
			}
			val[x] = '\0';
		}
		i++;
	}
	if (j == 0)
	{
		val = malloc(ft_strlen("not PWD") + 1);
		val = "not PWD";
	}
	return (val);
}

int	ft_check_n_echo(char *str)
{
	int i;

	i = 1;
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **arv)
{
	int i;
	int	n;

	i = 1;
	n = 0;
	if (nb_arv(arv) > 1)
	{
		if (ft_check_n_echo(arv[1]) == 0)
			n = 1;
		while (arv[i] != NULL && ft_check_n_echo(arv[i]) == 0)
			i++;
		while (arv[i])
		{
			printf("%s", arv[i]);
			if (arv[i + 1])
				printf(" ");
			i++;
		}
		if (n == 0)
			printf("\n");
	}
	return (0);
}

int	ft_pwd(t_exec_data *data)
{
	char buf[1000];

	if (getcwd(buf, sizeof(buf)))
		printf("%s\n", buf);
	else
		printf("my -->%s\n", data->pwd);
	return (0);
}

int ft_env(t_exec_data *data)
{
	t_env_list *env;

	env = data->head_env;
	while (env)
	{
		if (env->cont)
			printf("%s=%s\n", env->key, env->cont);
		env = env->next;
	}
	return (0);
}

int	ft_unset(t_exec_data *data)
{
	t_env_list *env;
	t_env_list *arv;
	t_env_list *tmp;
	t_env_list *prev;

	env = data->head_env;
	arv = data->arv_unset;
	if (!arv->next)
		exit(0);
	data->arv_unset = arv->next;
	dele_node(arv);
	arv = data->arv_unset;
	while (arv)
	{
		if (check_unset(arv->key) == 1)
		{
			ft_putstr_fd(arv->key, 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
		}
		else
		{
			while (env)
			{
				// printf("%s\n", env->key);
				if (ft_strncmp(env->key, arv->key, ft_strlen(env->key)) == 0)
				{
					if (env == data->head_env)
					{
						data->head_env = data->head_env->next;
						free(env);
						return (0);
					}
					tmp = env;
					prev->next = env->next;
					free(tmp);
					return (0);
				}
				prev = env;
				env = env->next;
			}
		}
		arv = arv->next;
	}
	return (0);
}

int	check_unset(char *str)
{
	int i;

	i = 1;
	if ((!ft_isalpha(str[0]) && str[0] != '_'))
	{
		return (1);
	}
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

