#include"../../include/minishell.h"

void	here_d(char *delimiter, t_exec_data *e_data, int len)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(delimiter, line) == 0)
			exit(0);
		else
		{
			if (line)
			{
				ft_putstr_fd(line, e_data->fd_her[len]);
				ft_putstr_fd("\n", e_data->fd_her[len]);
				free(line);
			}
		}
	}
}

char	*random_name(void)
{
	char	*name;
	char	buff;
	int		i;
	int		fd;

	name = malloc(10);
	i = 0;
	buff = '\0';
	fd = open("/dev/random", O_RDWR);
	while (i < 9)
	{
		read(fd, &buff, 1);
		if (buff >= 97 && buff <= 122)
		{
			name[i] = buff;
			i++;
		}
	}
	name[9] = 0;
	return (name);
}

char	*value_hd(char *value, char *delimiter)
{
	int		len;
	char	*ret;
	int		i;
	(void)delimiter;

	i = 0;
	ret = NULL;
	len = ft_strlen(value);
	ret = malloc(len + 1);
	while (value[len])
	{
		write(2, &value, 1);
		ret[i] = value[len];
		i++;
		len--;;
	}
	ret = ft_strndup(ret, ft_strlen(delimiter));
	// ft_putstr_fd(ret, 2);
	return(ret);
}

int	exec_herdoc(t_list *exec, t_exec_data *e_data)
{
	t_list	*node;
	char	*value;
	int		id_fork;
	int		len;
	int		i;

	node = exec;
	len = 0;
	value = NULL;
	e_data->fd_her = malloc(ft_lstsize(exec) * sizeof(int));
	while (node)
	{
		e_data->fd_her[len] = -2;
		if (((t_data *)node->content)->hd)
		{
			i = 0;
			while (((t_data *)node->content)->hd[i])
			{
				e_data->fd_her[len] = open(ft_strjoin(ft_strdup("/tmp/"), random_name()), O_CREAT | O_RDWR, 0644);
				if (e_data->fd_her[len] == -1)
				{
					((t_data *)exec->content)->inf = ft_strdup(((t_data *)node->content)->hd[i]);
					((t_data *)exec->content)->error = 1;
				}
				if (check_qaout(((t_data *)exec->content)->hd[i]))
				{
					value = (((t_data *)exec->content)->hd[i]);
         		   norm1(exec, &value, i);
				   value = value + ft_strlen(((t_data *)exec->content)->hd[i]);
				   ft_putstr_fd(value, 2);
				}
				g_glob.child = 1;
				id_fork = fork();
				if (id_fork == -1)
					ft_exit_bonus("error: failed in fork herdoc");
				if (id_fork == 0)
				{
					if (!value)
						here_d(((t_data *)node->content)->hd[i], e_data, len);
					else
						here_d(value, e_data, len);
				}
				wait(NULL);
				g_glob.child = 0;
				i++;
			}
		}
		len++;
		node = node->next;
	}
	return (0);
}
