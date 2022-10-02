#include"../../include/minishell.h"

void	ft_foork(t_exec_data *e_data)
{
	if (e_data->i == 0)
		start_foork(e_data);
	else
		end_foork(e_data);
}

void	start_foork(t_exec_data *e_data)
{
	if (e_data->infile != -2)
	{
		if (dup2(e_data->infile, 0) < 0)
			ft_exit_bonus("failed dup2 stdin first command");
	}
	else
	{
		if (e_data->fd_outfiles != -2)
		{
			if (dup2(e_data->fd_outfiles, 1) < 0)
				ft_exit_bonus("failed dup2 stdin first command");
		}
		else
		{
			if (e_data->nb_node != 1)
			{
				if (dup2(e_data->fd_pipe[e_data->i][1], 1) < 0)
					ft_exit_bonus("failed dup2 stdout first command");
			}
		}
	}
}

void	end_foork(t_exec_data *e_data)
{
	if (e_data->infile != -2)
	{
		if (dup2(e_data->infile, 0) < 0)
			ft_exit_bonus("failed dup2 stdin first command");
	}
	else
	{
		if (dup2(e_data->fd_pipe[e_data->i - 1][0], 0) < 0)
			ft_exit_bonus("failed dup2 stdin last command");
	}
	if (e_data->fd_outfiles != -2)
	{
		if (dup2(e_data->fd_outfiles, 1) < 0)
			ft_exit_bonus("failed dup2 stdout last command");
	}
}

void	middle_foork(t_exec_data *e_data)
{
	if (e_data->infile != -2)
	{
		if (dup2(e_data->infile, 0) < 0)
			ft_exit_bonus("failed dup2 stdin first command");
	}
	else
	{
		if (dup2(e_data->fd_pipe[e_data->i - 1][0], 0) < 0)
			ft_exit_bonus("failed dup2 stdin last command");
	}
	if (e_data->fd_outfiles != -2)
	{
		if (dup2(e_data->fd_outfiles, 1) < 0)
			ft_exit_bonus("failed dup2 stdout last command");
	}
	else
	{
		if (dup2(e_data->fd_pipe[e_data->i][1], 1) < 0)
			ft_exit_bonus("failed dup2 stdout last command");
	}
}

int	mult_pipe(t_exec_data *e_data, t_list *exec)
{
	sig_child();
	if (e_data->infile == -1)
	{
		ft_putstr_fd
		(ft_strjoin(ft_strdup
		(((t_data *)exec->content)->inf), ": No such file or directory\n"), 2);
		exit(1);
	}
	if (((t_data *)exec->content)->outfiles)
		ft_open_outfiles(e_data, exec);
	if (e_data->i == 0 || e_data->i == e_data->nb_node - 1)
		ft_foork(e_data);
	else
		middle_foork(e_data);
	if (e_data->fd_outfiles != -2 && e_data->fd_outfiles != -1)
		close(e_data->fd_outfiles);
	ft_close(e_data);
	if (e_data->name_built != NULL)
		exec_builtins(exec, e_data);
	else
		exec_cmd(exec, e_data);
	return (0);
}
