/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:58:47 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/29 15:44:42 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	just_equals(t_env_list *t_env, t_env_list *node)
{
	t_env_list	*env;
	char		*tmp;

	env = t_env;
	while (env)
	{
		if (ft_strcmp(env->key, node->key) == 0)
		{
			if (node->cont != '\0')
			{
				tmp = env->cont;
				env->cont = ft_strdup(node->cont);
				free(tmp);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	plus_equals(t_env_list *t_env, t_env_list *node)
{
	t_env_list	*env;
	char		*tmp;

	env = t_env;
	while (env)
	{
		if (ft_strncmp(env->key, node->key, ft_strlen(env->key)) == 0)
		{
			tmp = env->cont;
			env->cont = ft_strjoin(ft_strdup(env->cont), node->cont);
			free(tmp);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	printf_list_expo(t_env_list *list)
{
	t_env_list	*tmp;

	tmp = list;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", g_glob.fd_built);
		ft_putstr_fd(tmp->key, g_glob.fd_built);
		ft_putstr_fd(tmp->cont, g_glob.fd_built);
		ft_putstr_fd("\n", g_glob.fd_built);
		tmp = tmp->next;
	}
}

int	check_equal(char *str, int indec)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || indec < 1)
			return (1);
		i++;
	}
	return (0);
}
