/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:58:42 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/21 17:42:58 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	val_env_utl(char *val, char **env, int i)
{
	int		j;
	int		x;

	j = 0;
	x = 0;
	while (env[i][j] != '=')
		j++;
	while (env[i][++j])
	{
		val[x] = env[i][j];
		x++;
	}
	val[x] = '\0';
}

int	ft_env(t_exec_data *data, t_list *exec)
{
	t_env_list	*env;

	if (count_args(((t_data *)exec->content)->args) == 2)
	{
		env = data->head_env;
		while (env)
		{
			if (env->cont)
			{
				ft_putstr_fd(env->key, g_glob.fd_built);
				ft_putstr_fd("=", g_glob.fd_built);
				ft_putstr_fd(env->cont, g_glob.fd_built);
				ft_putstr_fd("\n", g_glob.fd_built);
			}
			env = env->next;
		}
	}
	else
	{
		ft_putstr_fd("No such file or directory\n", 2);
		g_glob.child = 127;
	}
	return (g_glob.child);
}

char	*val_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", ft_strlen("PWD")) == 0)
			return (ft_strdup(""));
		i++;
	}
	return (ft_strdup("PWD is unset"));
}

int	printf_list(t_env_list *list)
{
	t_env_list	*tmp;

	tmp = list;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, g_glob.fd_built);
		ft_putstr_fd("=", g_glob.fd_built);
		ft_putstr_fd(tmp->cont, g_glob.fd_built);
		ft_putstr_fd("\n", g_glob.fd_built);
		tmp = tmp->next;
	}
	return (0);
}
