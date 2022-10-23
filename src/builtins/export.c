/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:58:54 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/23 18:46:46 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	check_valid_enva_jout(char *str)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(str[0]) && str[0] != '_'))
		return (1);
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '\0')
			return (2);
		if ((!ft_isalpha(str[i]) && !ft_isalnum(str[i]) && str[i] != '_')
			|| (str[i] == '+' && str[i + 1] != '\0'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_export_arv(t_exec_data *data)
{
	t_env_list	*arv;

	arv = data->arv_list;
	data->arv_list = arv->next;
	dele_node(arv);
	lstadd_back_export(data);
	return (0);
}

int	ft_export(t_exec_data *data)
{
	if (data->nb_arv == 1)
	{
		with_alpha(data);
		without_alpha(data);
	}
	else
	{
		ft_export_arv(data);
		lstadd_back_plus(&data->head_env, data->key_without_cont);
	}
	return (g_glob.g_exit);
}

void	with_alpha(t_exec_data *data)
{
	int			alpha;
	t_env_list	*env;

	env = data->head_env;
	alpha = 'A';
	while (alpha <= 'Z')
	{
		while (env)
		{
			if (env->key[0] == alpha)
				put_with_alpha(env);
			env = env->next;
		}
		env = data->head_env;
		alpha++;
	}
}

void	without_alpha(t_exec_data *data)
{
	t_env_list	*env;

	env = data->head_env;
	while (env)
	{
		if (env->key[0] < 'A' || env->key[0] > 'Z')
		{
			if (env->cont)
			{
				ft_putstr_fd("declare -x ", g_glob.fd_built);
				ft_putstr_fd(env->key, g_glob.fd_built);
				ft_putstr_fd("=\"", g_glob.fd_built);
				ft_putstr_fd(env->cont, g_glob.fd_built);
				ft_putstr_fd("\"\n", g_glob.fd_built);
			}
			else
			{
				ft_putstr_fd("declare -x ", g_glob.fd_built);
				ft_putstr_fd(env->key, g_glob.fd_built);
				ft_putstr_fd("\n", g_glob.fd_built);
			}
		}
		env = env->next;
	}
}
