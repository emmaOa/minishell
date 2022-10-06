#include"../../include/minishell.h"

void	ft_foork(t_exec_data *e_data)
{
	if (e_data->i == 0)
	{
		ft_putstr_fd("start\n", 2);
		start_foork(e_data);
	}
	else
	{
		ft_putnbr_fd(e_data->i, 2);
		ft_putstr_fd("end\n", 2);
		end_foork(e_data);
	}
}

void	start_foork(t_exec_data *e_data)
{
	if (e_data->infile != -2)
	{
		ft_putstr_fd("infile_startfoork\n", 2);
		if (dup2(e_data->infile, 0) < 0)
			ft_exit_bonus("failed dup2 stdin first command0");
	}
	if (e_data->fd_outfiles != -2)
	{
		ft_putstr_fd("outfile_foork\n", 2);
		if (dup2(e_data->fd_outfiles, 1) < 0)
			ft_exit_bonus("failed dup2 stdin first command1");
	}
	else
	{
		if (e_data->nb_node != 1)
		{
			ft_putstr_fd("nb != 1\n", 2);
			ft_putnbr_fd(e_data->i, 2);
			if (e_data->name_built)
				g_glob.fd_built = e_data->fd_pipe[e_data->i][1];
			else
			{
				if (dup2(e_data->fd_pipe[e_data->i][1], 1) < 0)
				ft_exit_bonus("failed dup2 stdout first command2");
			}
		}
	}
		// ft_putstr_fd("standar\n", 2);
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
	sig_child();
	if (e_data->infile == -1)
	{
		ft_putstr_fd
		(ft_strjoin(ft_strdup
		(((t_data *)exec->content)->inf), ": No such file or directory\n"), 2);
		exit(1);
	}
	if (e_data->i == 0 || e_data->i == e_data->nb_node - 1)
	{
		ft_putstr_fd("foork\n", 2);
		ft_foork(e_data);
	}
	else
	{
		ft_putstr_fd("middle\n", 2);
		middle_foork(e_data);
	}
	ft_close(e_data);
	if (e_data->name_built != NULL)
		exec_builtins(exec, e_data);
	else if (((t_data *)exec->content)->args)
		exec_cmd(exec, e_data);
	return (0);
}
