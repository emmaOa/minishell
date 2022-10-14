/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:54:05 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/11 14:29:48 by iouazzan         ###   ########.fr       */
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
		{
			if (ft_strcmp(delimiter, line) == 0)
				free(line);
			exit(0);
		}
		else
		{
			if (line)
			{
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

int	exec_herdoc(t_list *exec, t_exec_data *e_data)
{
	t_list	*node;
	int		len;

	node = exec;
	len = 0;
	while (node)
	{
		e_data->fd_her[len] = -2;
		if (((t_data *)node->content)->hd)
		{
			mult_hd(exec, e_data, node, len);
		}
		len++;
		node = node->next;
	}
	return (0);
}

int	mult_hd(t_list *exec, t_exec_data *e_data, t_list *node, int len)
{
	char	*name_hd;
	char	*ran_nm;
	int		i;

	i = 0;
	name_hd = NULL;
	ran_nm = NULL;
	while (((t_data *)node->content)->hd[i])
	{
		ran_nm = random_name();
		name_hd = ft_strjoin(ft_strdup("/tmp/"), ran_nm);
		free(ran_nm);
		g_glob.expand_hd = 0;
		e_data->fd_her[len] = open(name_hd, O_CREAT | O_RDWR, 0666);
		if (if_cond
			(exec, ((t_data *)node->content)->hd[i], e_data->fd_her[len], i))
			((t_data *)node->content)->hd[i] = if_cond(exec,
					((t_data *)node->content)->hd[i], e_data->fd_her[len], i);
		g_glob.child = 1;
		fork_her(e_data, ((t_data *)node->content)->hd[i], e_data->fd_her[len]);
		g_glob.child = 0;
		close(e_data->fd_her[len]);
		e_data->fd_her[len] = open(name_hd, O_CREAT | O_RDWR, 0666);
		free(name_hd);
		i++;
	}
	return (0);
}

void	fork_her(t_exec_data *e_data, char *delimiter, int fd_her)
{
	int	id_fork;

	id_fork = fork();
	if (id_fork == -1)
		ft_exit_bonus("error: failed in fork herdoc");
	if (id_fork == 0)
		here_d(delimiter, e_data, fd_her);
	wait(NULL);
}

char	*if_cond(t_list *exec, char *delimiter, int fd_hr, int i)
{
	char	*value;

	value = NULL;
	if (fd_hr == -1)
	{
		((t_data *)exec->content)->inf = delimiter;
		((t_data *)exec->content)->error = 1;
	}
	if (check_qaout(delimiter))
	{
		norm1(exec, &value, i);
		g_glob.expand_hd = 1;
	}
	return (value);
}
