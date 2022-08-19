#include "minishell.h"

// int	ft_list_env(t_data	*data, char *env[])
// {
// 	int i;

// 	i = 0;
// 	data->head_list = &data->list_env;
// 	while (env[i])
// 	{
// 		ft_lstadd_back(data->head_list, ft_lstnew(env[i]));
// 		printf("%s\n", env[i]);
// 		// exit(0);
// 		i++;
// 	}
// 	return (0);
// }

int	main(int arc, char *arv[], char *env[])
{
	(void)env;
	int i;

	i = 0;
	if (arc > 1)
	{
		t_data	*data;
		data = malloc(sizeof(t_data));
		data->av = arv;
		data->ac = arc;
		ft_pwd(data);
		ft_echo(data);
		// ft_export(data);
	}
	return (0);
}