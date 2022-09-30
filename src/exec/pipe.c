#include"../../include/minishell.h"

int	ft_pipe(t_exec_data *data)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	errno = 0;
	data->fd_pipe = (int **)malloc((data->nb_node + 1) * sizeof(int *));
	while (x < data->nb_node)
	{
		data->fd_pipe[x] = (int *)malloc(2 * sizeof(int));
		x++;
	}
	while (i < data->nb_node)
	{
		if (pipe(data->fd_pipe[i]) == -1)
		{
			printf("error: pipe failed%s\n", strerror(errno));
			exit(errno);
		}
		i++;
	}
	return (0);
}
