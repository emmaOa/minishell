/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:40 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/17 00:40:03 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	ft_foork(t_exec_data *e_data)
{
	if (e_data->i == 0)
		start_foork(e_data);
	else
		end_foork(e_data);
}

void	end_foork(t_exec_data *e_data)
{
	if (e_data->infile != -2)
	{
		if (dup2(e_data->infile, 0) < 0)
			ft_exit("failed dup2 stdin first command\n", 1);
	}
	else
	{
		if (dup2(e_data->fd_pipe[e_data->i - 1][0], 0) < 0)
			ft_exit("failed dup2 stdin last command\n", 1);
	}
	if (e_data->fd_outfiles != -2)
	{
		if (dup2(e_data->fd_outfiles, 1) < 0)
			ft_exit("failed dup2 stdout last command\n", 1);
	}
}

void	middle_foork(t_exec_data *e_data)
{
	if (e_data->infile != -2)
	{
		if (dup2(e_data->infile, 0) < 0)
			ft_exit("failed dup2 stdin first command\n", 1);
	}
	else
	{
		if (dup2(e_data->fd_pipe[e_data->i - 1][0], 0) < 0)
			ft_exit("failed dup2 stdin last command\n", 1);
	}
	if (e_data->fd_outfiles != -2)
	{
		if (dup2(e_data->fd_outfiles, 1) < 0)
			ft_exit("failed dup2 stdout last command\n", 1);
	}
	else
	{
		if (e_data->name_built)
			g_glob.fd_built = e_data->fd_pipe[e_data->i][1];
		else
		{
			if (dup2(e_data->fd_pipe[e_data->i][1], 1) < 0)
				ft_exit("failed dup2 stdout last command\n", 1);
		}
	}
}

int	mult_pipe(t_exec_data *e_data, t_list *exec)
{
	char	*error;

	sig_child();
	error = ": No such file or directory\n";
	if (e_data->infile == -1)
	{
		error = ft_strjoin(ft_strdup
				(((t_data *)exec->content)->inf), error);
		ft_putstr_fd(error, 2);
		free(error);
		exit (1);
	}
	if (e_data->i == 0 || e_data->i == e_data->nb_node - 1)
		ft_foork(e_data);
	else
		middle_foork(e_data);
	ft_close(e_data);
	if (e_data->name_built != NULL)
		exec_builtins(exec, e_data);
	else if (((t_data *)exec->content)->args)
		exec_cmd(exec, e_data);
	else
		exit (0);
	return (0);
}
