#include "minishell.h"

char *ft_strndup(char *str, int len)
{
	char	*c;
	size_t	i;

	i = 0;
	c = ft_calloc(len + 1, sizeof(char));
	if (!c)
		return (NULL);
	while (i < len)
	{
		c[i] = str[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}