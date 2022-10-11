/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fd_built.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:03:27 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/10 18:03:42 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	put_with_alpha(t_env_list	*env)
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
