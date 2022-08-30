#include "minishell.h"

int	main(int arc, char *arv[], char *env[])
{
	int i;

	i = 0;
	if (arc > 1)
	{
		t_data	*data;
		data = malloc(sizeof(t_data));
		data->head = NULL;
		data->arv_list = NULL;
		data->head_env = NULL;
		data->av = arv;
		data->ac = arc;
		data->ev = env;
		data->head_env = arr_to_list(data, env);
		data->arv_list = arv_to_list(data, arv);
		// printf_list_env(data->head_env );
		// printf("%s%s\n", data->head_env->key, data->head_env->cont)
		// lstadd_back(&data->head_env, data->key_without_cont);
		// printf_list_env(data->head_env);
		// exit(0);
		ft_pwd(data);
		ft_echo(data);
		ft_export(data);
	}
	//<<< function to use >>>
	//	- int		list_to_arr(t_data *data);
	//	- void		printf_list_env(t_env_list *list);
	return (0);
}