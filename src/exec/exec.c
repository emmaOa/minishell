/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:32 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/17 00:39:49 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	execution(t_exec_data *e_data, t_list *exec)
{
	if (((t_data *)exec->content)->args)
	{
		if (e_data->fd_outfiles != -2)
			g_glob.fd_built = e_data->fd_outfiles;
		if (e_data->nb_node == 1 && e_data->name_built)
		{
			if (e_data->name_built)
			{
				exec_builtins(exec, e_data);
				e_data->name_built = NULL;
			}
		}
		else if (!e_data->name_built)
			mult_cmd(e_data, exec);
		if (e_data->fd_outfiles != -2)
		{
			e_data->fd_outfiles = -2;
			g_glob.fd_built = 1;
		}
	}
	return (0);
}

int	out_file(t_exec_data *e_data, t_list *exec)
{
	if (((t_data *)exec->content)->outfiles
		|| ((t_data *)exec->content)->append)
		ft_open_outfiles(e_data, exec);
	return (0);
}

int	mult_cmd(t_exec_data *e_data, t_list *exec)
{
	out_file(e_data, exec);
	e_data = is_builtins(exec, e_data);
	g_glob.child = 1;
	e_data->forck = fork();
	if (e_data->forck == -1)
		ft_exit("error: failed in fork\n", 10);
	if (e_data->forck == 0)
		mult_pipe(e_data, exec);
	return (0);
}
