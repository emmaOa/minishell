#include"../../include/minishell.h"

int	ft_echo(char **arv)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (nb_arv(arv) > 1)
	{
		if (ft_check_n_echo(arv[1]) == 0)
			n = 1;
		while (arv[i] != NULL && ft_check_n_echo(arv[i]) == 0)
			i++;
		while (arv[i])
		{
			printf("%s", arv[i]);
			if (arv[i + 1])
				printf(" ");
			i++;
		}
		if (n == 0)
			printf("\n");
	}
	return (0);
}

int	ft_check_n_echo(char *str)
{
	int	i;

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