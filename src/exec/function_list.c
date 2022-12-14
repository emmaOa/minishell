/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:46 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/17 19:43:46 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

char	*check_home(t_exec_data *e_data)
{
	char	**env;
	int		i;

	i = 0;
	env = list_to_arr(e_data->head_env);
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")) == 0)
		{
			free_2d_array(env);
			return (check_home_utl(i, e_data));
		}
		i++;
	}
	ft_putstr_fd("HOME not found\n", 2);
	free_2d_array(env);
	return (NULL);
}

char	*check_home_utl(int i, t_exec_data *e_data)
{
	int		x;
	int		j;
	char	*path;
	char	**env;

	x = 0;
	env = list_to_arr(e_data->head_env);
	path = malloc(ft_strlen(env[i]) - ft_strlen("HOME"));
	j = 0;
	while (env[i][j] != '=')
		j++;
	j++;
	while (env[i][j])
	{
		path[x] = env[i][j];
		x++;
		j++;
	}
	free_2d_array(env);
	path[x] = '\0';
	return (path);
}

t_env_list	*ft_lstlast_mini(t_env_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

int	ft_lstsize_mini(t_env_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

t_env_list	*ft_lstnew_mini(void *key, void *cont)
{
	t_env_list	*new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->cont = cont;
	new->key = key;
	new->next = NULL;
	return (new);
}
