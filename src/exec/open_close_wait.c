#include"../../include/minishell.h"

int	ft_open_outfiles(t_exec_data *data, t_list *exec)
{
	int		i;
	char	**name_files;

	i = 0;
	errno = 0;
	name_files = ((t_data *)exec->content)->outfiles;
	if (name_files)
	{
		while (i < count_args(name_files))
		{
			data->fd_outfiles = open(name_files[i], O_CREAT | O_RDWR, 0666);
			if (data->fd_outfiles == -1)
			{
				perror(strerror(errno));
				exit (errno);
			}
			i++;
		}
	}
	return (0);
}

void	ft_wait(t_exec_data *e_data)
{
	int	i;

	i = 0;
	while (i < e_data->nb_node)
	{
		wait(NULL);
		i++;
	}
	g_glob.child = 0;
	sig_main();
}

void	ft_close(t_exec_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_node)
	{
		close(data->fd_pipe[i][0]);
		close(data->fd_pipe[i][1]);
		i++;
	}
}
