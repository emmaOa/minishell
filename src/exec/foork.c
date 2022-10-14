/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:40 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/10 18:08:58 by iouazzan         ###   ########.fr       */
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
			ft_exit_bonus("failed dup2 stdin first command3");
	}
	else
	{
		if (dup2(e_data->fd_pipe[e_data->i - 1][0], 0) < 0)
			ft_exit_bonus("failed dup2 stdin last command4");
	}
	if (e_data->fd_outfiles != -2)
	{
		if (dup2(e_data->fd_outfiles, 1) < 0)
			ft_exit_bonus("failed dup2 stdout last command5");
	}
}

void	middle_foork(t_exec_data *e_data)
{
	if (e_data->infile != -2)
	{
		if (dup2(e_data->infile, 0) < 0)
			ft_exit_bonus("failed dup2 stdin first command6");
	}
	else
	{
		if (dup2(e_data->fd_pipe[e_data->i - 1][0], 0) < 0)
			ft_exit_bonus("failed dup2 stdin last command7");
	}
	if (e_data->fd_outfiles != -2)
	{
		if (dup2(e_data->fd_outfiles, 1) < 0)
			ft_exit_bonus("failed dup2 stdout last command8");
	}
	else
	{
		if (e_data->name_built)
			g_glob.fd_built = e_data->fd_pipe[e_data->i][1];
		else
		{
			if (dup2(e_data->fd_pipe[e_data->i][1], 1) < 0)
				ft_exit_bonus("failed dup2 stdout last command9");
		}
	}
}

int	mult_pipe(t_exec_data *e_data, t_list *exec)
{
	char	*error;


	sig_child();
	if (e_data->infile == -1)
	{
		error = ft_strjoin(ft_strdup
		(((t_data *)exec->content)->inf), ": No such file or directory\n");
		ft_putstr_fd(error, 2);
		free(error);
		exit(1);
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
