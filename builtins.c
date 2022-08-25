 #include "minishell.h"

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

int	ft_echo(t_data *data)
{
	int i;
	int	n;

	i = 2;
	n = 0;
	if (data->ac > 2)
	{
		if (ft_strncmp("echo", data->av[1], ft_strlen(data->av[1])) == 0)
		{
			if (ft_check_n_echo(data->av[2]) == 0)
				n = 1;
			while (data->av[i] != NULL && ft_check_n_echo(data->av[i]) == 0)
				i++;
			while (data->av[i])
			{
				printf("%s", data->av[i]);
				if (data->av[i + 1])
					printf(" ");
				i++;
			}
			if (n == 0)
				printf("\n");
		}
	}

	return (0);
}
int	ft_pwd(t_data *data)
{
	char buf[1000];
	if (ft_strncmp("pwd", data->av[1], ft_strlen(data->av[1])) == 0)
	{
		getcwd(buf, sizeof(buf));
		printf("%s", buf);
	}
	return (0);
}
