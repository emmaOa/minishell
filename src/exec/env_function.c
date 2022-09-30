#include"../../include/minishell.h"

char	*key_evn(char *str)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	len = i;
	key = malloc(len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = str[i];
		i++;
	}
	key[len] = '\0';
	return (key);
}

char	*cont_evn(char *env)
{
	int		i;
	int		j;
	char	*cont;

	i = 0;
	j = 0;
	cont = malloc(ft_strlen(env));
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] != '=' || env[i + 1] == '\0')
		cont[j] = '\0';
	else
	{
		i++;
		while (env[i])
		{
			cont[j] = env[i];
			i++;
			j++;
		}
		cont[j] = '\0';
	}
	return (cont);
}
