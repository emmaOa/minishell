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
		ft_pwd(data);
		ft_echo(data);
		ft_export(data);
	}
	//<<< function to use >>>
	//	- int		list_to_arr(t_data *data);
	//	- void		printf_list_env(t_env_list *list);
	// t_env_list	*ft_lstnew_mini(void *key, void *cont);
	// t_env_list	*ft_lstlast_mini(t_env_list *lst);
	// void		dele_node(t_env_list *node);
	// void		check_dele(t_env_list *data, t_env_list *node);
	// int			ft_lstsize_mini(t_env_list *lst);
	return (0);
}