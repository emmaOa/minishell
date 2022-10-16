/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:06 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/16 17:44:02 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	check_unset(char *str)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(str[0]) && str[0] != '_'))
	{
		return (1);
	}
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset_utl(t_exec_data *data, char *key)
{
	t_env_list	*env;
	t_env_list	*tmp;
	t_env_list	*prev;

	env = data->head_env;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			if (env == data->head_env)
			{
				data->head_env = data->head_env->next;
				free(env);
				return (1);
			}
			tmp = env;
			prev->next = env->next;
			free(tmp);
			return (1);
		}
		prev = env;
		env = env->next;
	}
	return (0);
}

int	ft_unset(t_exec_data *data)
{
	t_env_list	*arv;

	arv = data->arv_unset;
	if (!arv->next)
		return (0);
	data->arv_unset = arv->next;
	dele_node(arv);
	arv = data->arv_unset;
	while (arv)
	{
		if (check_unset(arv->key) == 1)
		{
			ft_putstr_fd(arv->key, 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
		}
		else
		{
			if (ft_unset_utl(data, arv->key) == 1)
				return (0);
		}
		arv = arv->next;
	}
	return (0);
}

void	arv_unset(t_exec_data *data, char *str[])
{
	int			i;
	t_env_list	*tmp;

	i = 0;
	data->arv_unset = NULL;
	while (str[i])
	{
		tmp = malloc(sizeof(t_env_list));
		tmp->key = str[i];
		tmp->cont = "\0";
		tmp->next = NULL;
		lstadd_back(&data->arv_unset, tmp);
		i++;
	}
	return ;
}
