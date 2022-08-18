#include "minishell.h"

int	ft_list_env(t_data	*data, char *env[])
{
	
}

int	main(int arc, char *arv[], char *env[])
{
	if (arc > 1)
	{
		t_data	*data;
		data = malloc(sizeof(t_data));
		data->av = arv;
		data->ac = arc;
		ft_list_env(data, env);
		ft_echo(data);
	}
	return (0);
}