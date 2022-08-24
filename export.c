#include "minishell.h"

int	ft_export(t_data *data, char *env[])
{
	int	i;
	int	j;

	i = 0;
	if (ft_strncmp("export", data->av[1], ft_strlen(data->av[1])) == 0)
	{
		while (env[i])
		{
			printf("declare -x ");
			j = 0;
			while (env[i][j])
			{
				printf("%c", env[i][j]);
				if (env[i][j] == '=')
					printf("\"");
				j++;
			}
			printf("\"\n");
			i++;
		}
	}
	return (0);
}
