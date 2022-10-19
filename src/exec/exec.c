/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:32 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/19 17:09:13 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

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
	{
		ft_putstr_fd("fork: Resource temporarily unavailable\n", 2);
		return (1);
	}
	if (e_data->forck == 0)
		mult_pipe(e_data, exec);
	return (0);
}
