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

int	ft_strcmp(const char *d, const char *s)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*src;

	i = 0;
	dst = (unsigned char *)d;
	src = (unsigned char *)s;
	while ((dst[i] != '\0') || (src[i] != '\0'))
	{
		if (dst[i] != src[i])
			return (1);
		i++;
	}
	return (0);
}