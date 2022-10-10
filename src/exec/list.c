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
			e_data->infile = -2;
			e_data->fd_outfiles = -2;
			if (e_data->fd_her[e_data->i] != -2)
				e_data->infile = e_data->fd_her[e_data->i];
			if (e_data->infile != -2 || ((t_data *)exec->content)->infiles)
				e_data->infile = check_inf(((t_data *)exec->content)->infiles, ((t_data *)exec->content)->n_infiles, e_data);
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
		e_data->infile = check_inf(((t_data *)exec->content)->infiles, ((t_data *)exec->content)->n_infiles, e_data);
	out_file(e_data, exec);
	e_data = is_builtins(exec, e_data);
	if (e_data->name_built)
	{
		if (e_data->fd_outfiles != -2)
			g_glob.fd_built = e_data->fd_outfiles;
		exec_builtins(exec, e_data);
		e_data->name_built = NULL;
	}
	return (0);
}
