#include"../../include/minishell.h"

void	ft_exit_bonus(char *s)
{
	perror(s);
	exit(0);
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

int	ft_pipe(t_exec_data *data)
{
	int	x;
	int i;

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

int	ft_open_outfiles(t_exec_data *data, t_list *exec)
{
	int i;
	char **name_files;

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

void	ft_foork(t_exec_data *e_data, t_list *exec)
{
	if (e_data->i == 0)
	{
		if (((t_data *)exec->content)->infiles != -2)
		{
			if (dup2(((t_data *)exec->content)->infiles, 0) < 0)
				ft_exit_bonus("failed dup2 stdin first command");
		}
		else
		{
			if (e_data->fd_outfiles != -2)
			{
				// ft_putnbr_fd(123, 2);
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
	else
	{
		// ft_putnbr_fd(321, 2);
		if (((t_data *)exec->content)->infiles != -2)
		{
			if (dup2(((t_data *)exec->content)->infiles, 0) < 0)
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
}

int	mult_pipe(t_exec_data *e_data, t_list *exec)
{
	if (((t_data *)exec->content)->infiles == -1)
	{
		ft_putstr_fd(ft_strjoin(((t_data *)exec->content)->inf, ": No such file or directory\n"), 2);
		exit(1);
	}
	if (((t_data *)exec->content)->outfiles)
		ft_open_outfiles(e_data, exec);
	if (e_data->i == 0 || e_data->i == e_data->nb_node - 1)
		ft_foork(e_data, exec);
	else
	{
		if (((t_data *)exec->content)->infiles != -2)
		{
			if (dup2(((t_data *)exec->content)->infiles, 0) < 0)
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
	// if (((t_data *)exec->content)->infiles != -2)
	// 	close(((t_data *)exec->content)->infiles);
	if (e_data->fd_outfiles != -2 && e_data->fd_outfiles != -1)
		close(e_data->fd_outfiles);
	ft_close(e_data);
	if (e_data->name_built != NULL)
		exec_builtins(exec, e_data);
	else
		exec_cmd(e_data, exec);
	return (0);
}

int	ft_len_2d(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
		i++;
	return (i);
}

void	ft_wait(t_exec_data *e_data)
{
	int i;

	i = 0;
	while (i < e_data->nb_node)
	{
		wait(NULL);
		i++;
	}
}

void	ft_free_int(int **tabl, int start, int len)
{
	while (start < len)
	{
		free(tabl[start]);
		start++;
	}
	free(tabl);
}

char	*ft_path(char *env[])
{
	int		i;
	char	*pt;
	char	*tmp;

	i = 0;
	tmp = NULL;
	pt = "PATH";
	while (env[i])
	{
		if (ft_strncmp(env[i], pt, ft_strlen(pt)) == 0)
			tmp = env[i];
		i++;
	}
	if (!tmp)
		ft_exit_bonus("path not founde: ");
	i = 0;
	while (tmp[i] && tmp[i] != '=')
	{
		tmp[i] = tmp[i + 1];
		i++;
	}
	return (tmp);
}

char	*ft_url(char *path, t_list *exec)
{
	int		i;
	char	**url;
	char	*cmd_path;

	i = 0;
	if (ft_strchr(((t_data *)exec->content)->args[0], '/'))
	{
		if (access(((t_data *)exec->content)->args[0], F_OK) == 0)
			return (((t_data *)exec->content)->args[0]);
		return (NULL);
	}
	url = ft_split(path, ':');
	while (url[i])
	{
		cmd_path = ft_strjoin(url[i], "/");
		cmd_path = ft_strjoin(cmd_path, ((t_data *)exec->content)->args[0]);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	exec_cmd(t_exec_data *e_data, t_list *exec)
{
	(void)e_data;
	char *url;

	url = ft_url(ft_path(((t_data *)exec->content)->envp), exec);
	if (url == NULL)
		ft_exit_bonus("command not founde");
	if (execve(url, ((t_data *)exec->content)->args, ((t_data *)exec->content)->envp) < 0)
		ft_exit_bonus("command not execute");
}