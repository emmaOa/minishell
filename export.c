#include "minishell.h"

int		ft_export_arv(t_data *data)
{
	return (0);
}

int	ft_export(t_data *data)
{
	int	i;
	int	j;
	int	alpha;
	t_env_list *tmp;

	i = 0;
	alpha = 'A';
	tmp = *data->head_env;
	if (data->ac == 2)
	{
		if (ft_strncmp("export", data->av[1], ft_strlen(data->av[1])) == 0)
		{
			while (alpha <= 'Z')
			{
				while (tmp->next)
				{
					if (tmp->key[0] == alpha)
						printf("declare -x %s\"%s\"\n", tmp->key, tmp->cont);
					tmp = tmp->next;
				}
				tmp = *data->head_env;
				alpha++;
			}
			while (tmp->next)
			{
				if (tmp->key[0] < 'A' || tmp->key[0] > 'Z')
					printf("declare -x %s\"%s\"\n", tmp->key, tmp->cont);
				tmp = tmp->next;
			}
		}
	}
	else
		ft_export_arv(data);
	return (0);
}
