#include "../../include/minishell.h"

int	nb_arv(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strndup(char *str, int len)
{
	char *c;
	int  i;

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

// int	ft_strcmp(const char *d, const char *s)
// {
// 	size_t			i;
// 	unsigned char	*dst;
// 	unsigned char	*src;

// 	i = 0;
// 	dst = (unsigned char *)d;
// 	src = (unsigned char *)s;
// 	while ((dst[i] != '\0') && (src[i] != '\0'))
// 	{
// 		if (dst[i] != src[i])
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	check_dele(t_env_list *t_list, t_env_list *node)
// {
// 	t_env_list *list;
// 	t_env_list *tmp;
// 	int	i;

// 	list = t_list;
// 	i = 0;
// 	while (list->next)
// 	{
// 		if (ft_strcmp(list->key, node->key) == 0)
// 		{
// 			if (i == 0)
// 				t_list = list->next;
// 			tmp = list->next;
// 			dele_node(list);
// 			list = tmp->next;
// 		}
// 		list = list->next;
// 		i++;
// 	}
// }

void	dele_node(t_env_list *node)
{
	if (!node)
		return ;
	node->cont = NULL;
	node->key = NULL;
	free(node);
	return ;
}