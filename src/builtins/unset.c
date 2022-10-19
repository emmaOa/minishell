/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:06 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/19 13:37:47 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	check_unset(char *str)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(str[0]) && str[0] != '_'))
		return (1);
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
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
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env == data->head_env)
			{
				data->head_env = data->head_env->next;
				dele_node(env);
				return (1);
			}
			tmp = env;
			prev->next = env->next;
			dele_node(tmp);
			return (1);
		}
		prev = env;
		env = env->next;
	}
	return (0);
}

int	ft_unset(t_exec_data *data, t_list *exec)
{
	char	**str;
	int		i;

	i = 1;
	str = ((t_data *)exec->content)->args;
	while (str[i])
	{
		if (check_unset(str[i]) == 1)
		{
			ft_putstr_fd(str[i], 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
		}
		else
		{
			if (ft_unset_utl(data, str[i]) == 1)
				return (0);
		}
		i++;
	}
	return (0);
}
