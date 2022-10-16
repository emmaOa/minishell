/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:00:05 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/16 18:31:29 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	list(t_exec_data *e_data, t_list *exec)
{
	e_data->nb_node = ft_lstsize(exec);
	e_data = is_builtins(exec, e_data);
	if (e_data->nb_node > 1 || (e_data->nb_node == 1 && !e_data->name_built))
	{
		ft_pipe(e_data);
		e_data->i = 0;
		while (exec)
		{
			init_in_out(e_data);
			if (e_data->fd_her[e_data->i] != -2)
				e_data->infile = e_data->fd_her[e_data->i];
			if (e_data->infile != -2 || ((t_data *)exec->content)->infiles)
				e_data->infile = check_inf(((t_data *)exec->content)->infiles,
						((t_data *)exec->content)->n_infiles, e_data);
			mult_cmd(e_data, exec);
			e_data->i++;
			exec = exec->next;
		}
		ft_close(e_data);
		free_bonus_int(e_data->fd_pipe, 0, e_data->nb_node);
		ft_wait(e_data);
	}
	else if (e_data->nb_node == 1 && e_data->name_built)
		list_one_node(e_data, exec);
	return (0);
}

int	list_one_node(t_exec_data *e_data, t_list *exec)
{
	if (((t_data *)exec->content)->infiles)
		e_data->infile = check_inf(((t_data *)exec->content)->infiles,
				((t_data *)exec->content)->n_infiles, e_data);
	if (e_data->infile == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		g_glob.g_exit = 1;
		return (0);
	}
	out_file(e_data, exec);
	e_data = is_builtins(exec, e_data);
	if (e_data->name_built)
	{
		if (e_data->fd_outfiles != -2)
			g_glob.fd_built = e_data->fd_outfiles;
		exec_builtins(exec, e_data);
		close(e_data->fd_outfiles);
		e_data->name_built = NULL;
	}
	return (0);
}
