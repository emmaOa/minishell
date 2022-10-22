/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:00 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/21 17:41:14 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	ft_pwd(t_exec_data *data)
{
	char	buf[1000];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putstr_fd(buf, g_glob.fd_built);
		ft_putstr_fd("\n", g_glob.fd_built);
	}
	else
	{
		ft_putstr_fd(data->pwd, g_glob.fd_built);
		ft_putstr_fd("\n", g_glob.fd_built);
	}
	return (g_glob.g_exit);
}
