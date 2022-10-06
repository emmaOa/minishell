#include"../../include/minishell.h"

int execution(t_exec_data *e_data, t_list *exec)
{
	if (((t_data *)exec->content)->args)
	{
		// printf("execution\n");
		if (e_data->fd_outfiles != -2)
			g_glob.fd_built = e_data->fd_outfiles;
		if (e_data->nb_node == 1 && e_data->name_built)
		{
			printf("node_1\n");
			if (e_data->name_built)
			{
				printf("built_1\n");
				exec_builtins(exec, e_data);
				e_data->name_built = NULL;
			}
		}
		else if (!e_data->name_built)
		{
			printf("cmnd\n");
			mult_cmd(e_data, exec);
		}
		if (e_data->fd_outfiles != -2)
		{
			e_data->fd_outfiles = -2;
			g_glob.fd_built = 1;
			ft_putstr_fd("close\n", 2);
		}
	}
	return (0);
}


int	out_file(t_exec_data *e_data, t_list *exec)
{
	if (((t_data *)exec->content)->outfiles != NULL)
		ft_open_outfiles(e_data, exec);
	return (0);
}

int	mult_cmd(t_exec_data *e_data, t_list *exec)
{
	e_data->infile = -2;
	e_data->fd_outfiles = -2;
	if (((t_data *)exec->content)->infiles)
		e_data->infile = check_inf(((t_data *)exec->content)->infiles,((t_data *)exec->content)->n_infiles, e_data->i, e_data);
	out_file(e_data, exec);
	e_data = is_builtins(exec, e_data);
	e_data->forck = fork();
	if (e_data->forck == -1)
		ft_exit_bonus("error: failed in fork");
	g_glob.child = 1;
	if (e_data->forck == 0)
		mult_pipe(e_data, exec);

	return (0);
}