#include "../../include/minishell.h"

t_exec_data	*is_builtins(t_list *exec)
{
	char **arv;
	t_exec_data *e_data;
	int i;

	arv = ((t_data *)exec->content)->args;
	e_data = malloc(sizeof(t_exec_data));
	e_data->head_env =  arr_to_list(e_data, ((t_data *)exec->content)->envp);
	e_data->arv_list = arv_to_list(e_data, arv);
	e_data->name_built = NULL;
	i = 0;
	if ((ft_strncmp(arv[0], "echo", ft_strlen("echo")) == 0)
		|| (ft_strncmp(arv[0], "pwd", ft_strlen("pwd")) == 0)
		|| (ft_strncmp(arv[0], "export", ft_strlen("export")) == 0)
		|| (ft_strncmp(arv[0], "env", ft_strlen("env")) == 0)
		|| (ft_strncmp(arv[0], "exit", ft_strlen("exit")) == 0)
		|| (ft_strncmp(arv[0], "unset", ft_strlen("unset")) == 0)
		|| (ft_strncmp(arv[0], "cd", ft_strlen("cd")) == 0))
			e_data->name_built = arv[0];
	return 	(e_data);
}
