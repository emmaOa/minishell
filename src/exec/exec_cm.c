#include"../../include/minishell.h"

void	exec_cmd(t_list *exec, t_exec_data *e_data)
{
	char	*url;
	char	**env;

	env = list_to_arr(e_data->head_env);
	url = ft_url(ft_path(env), exec);
	if (url == NULL)
		ft_exit_bonus("command not founde");
	if (execve(url, ((t_data *)exec->content)->args, env) < 0)
		ft_exit_bonus("command not execute");
}

void	ft_p(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("------>: %s <------\n", str[i]);
		i++;
	}
}

void	free_bonus_int(int **tabl, int start, int len)
{
	while (start < len)
	{
		free(tabl[start]);
		start++;
	}
	free(tabl);
}

void	ft_free_int(int **tabl, int start, int len)
{
	while (start < len)
	{
		free(tabl[start]);
		start++;
	}
	free(tabl);
}

void	ft_exit_bonus(char *s)
{
	perror(s);
	exit(0);
}
