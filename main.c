#include "minishell.h"

int	main(int arc, char *arv[], char *env[])
{
	int i;

	i = 0;
	if (arc > 1)
	{
		t_data	*data;
		data = malloc(sizeof(t_data));
		data->av = arv;
		data->ac = arc;
		data->ev = env;
		data->head_env = arr_to_list(data, env);
		ft_pwd(data);
		ft_echo(data);
		ft_export(data);
	}
	//function to use
	//	int		list_to_arr(t_data *data);
	//	void	printf_list_env(t_env_list **list);
	return (0);
}