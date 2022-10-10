/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:54:05 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/10 16:26:56 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	here_d(char *delimiter, t_exec_data *e_data, int fd_hd)
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
				ft_putnbr_fd(e_data->infile, 2);
				if (g_glob.expand_hd == 0 && check_exp(line) == 1)
					ft_putstr_fd(ft_ex_hd(line, e_data), fd_hd);
				else
					ft_putstr_fd(line, fd_hd);
				ft_putstr_fd("\n", fd_hd);
				free(line);
			}
		}
	}
}

int	check_exp(char *line)
{
	if (line[0] == '$')
		return (1);
	else
		return (0);
}

char	*ft_ex_hd(char *line, t_exec_data *e_data)
{
	t_env_list	*env;

	env = e_data->head_env;
	while (env)
	{
		if (ft_strcmp((line + 1), env->key) == 0)
			return (env->cont);
		env = env->next;
	}
	return ("");
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
				g_glob.expand_hd = 0;
				e_data->fd_her[len] = open(ft_strjoin(ft_strdup("/tmp/"), random_name()), O_CREAT | O_RDWR, 0666);
				ft_putstr_fd("----->>>>", 2);
				ft_putnbr_fd(e_data->fd_her[len], 2);
				if (e_data->fd_her[len] == -1)
				{
					((t_data *)exec->content)->inf = ft_strdup(((t_data *)node->content)->hd[i]);
					((t_data *)exec->content)->error = 1;
				}
				e_data->infile = e_data->fd_her[len];
				if (check_qaout(((t_data *)node->content)->hd[i]))
				{
        			norm1(exec, &value, i);
					((t_data *)node->content)->hd[i] = value;
					g_glob.expand_hd = 1;
				}
				g_glob.child = 1;
				id_fork = fork();
				if (id_fork == -1)
					ft_exit_bonus("error: failed in fork herdoc");
				if (id_fork == 0)
					here_d(((t_data *)node->content)->hd[i], e_data, e_data->fd_her[len]);
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
