/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:52 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/24 02:41:56 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_arv(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strndup(char *str, int len)
{
	int		i;
	char	*c;

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

void	dele_node(t_env_list *node)
{
	if (!node)
		return ;
	if (node->cont)
		free(node->cont);
	free(node->key);
	free(node);
	return ;
}

char	**list_to_arr(t_env_list *env)
{
	t_env_list	*tmp;
	char		**ev;
	int			i;

	i = 0;
	tmp = env;
	ev = (char **)malloc((ft_lstsize_mini(env) + 1) * sizeof(char *));
	while (tmp)
	{
		ev[i] = ft_strjoin(ft_strdup(tmp->key), "=");
		ev[i] = ft_strjoin(ev[i], tmp->cont);
		tmp = tmp->next;
		i++;
	}
	ev[i] = 0;
	return (ev);
}
