/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_foork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:08:26 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/15 21:49:26 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	start_foork(t_exec_data *e_data)
{
	if (e_data->infile != -2)
	{
		if (dup2(e_data->infile, 0) < 0)
			ft_exit("failed dup2 stdin first command", 1);
	}
	if (e_data->fd_outfiles != -2)
	{
		if (dup2(e_data->fd_outfiles, 1) < 0)
			ft_exit("failed dup2 stdin first command", 1);
	}
	else
		start_foork_n_out(e_data);
}

void	start_foork_n_out(t_exec_data *e_data)
{
	if (e_data->nb_node != 1)
	{
		if (e_data->name_built)
			g_glob.fd_built = e_data->fd_pipe[e_data->i][1];
		else
		{
			if (dup2(e_data->fd_pipe[e_data->i][1], 1) < 0)
				ft_exit("failed dup2 stdout first command", 1);
		}
	}
}
