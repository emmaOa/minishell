/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_wait.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:00:17 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/16 22:06:17 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	ft_open_outfiles(t_exec_data *data, t_list *exec)
{
	int		i;
	char	**name_files;

	i = 0;
	errno = 0;
	if (((t_data *)exec->content)->append)
		ft_append(data, exec);
	else
	{
		name_files = ((t_data *)exec->content)->outfiles;
		if (name_files)
		{
			while (i < count_args(name_files) - 1)
			{
				data->fd_outfiles = open(name_files[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
				if (data->fd_outfiles == -1)
				{
					perror(strerror(errno));
					exit (errno);
				}
				i++;
			}
		}
	}

	return (0);
}

void	ft_append(t_exec_data *data, t_list *exec)
{
	int		i;
	char	**name_files;

	i = 0;
	errno = 0;
	name_files = ((t_data *)exec->content)->append;
	if (name_files)
	{
		while (i < count_args(name_files) - 1)
		{
			data->fd_outfiles = open(name_files[i], O_CREAT | O_RDWR | O_APPEND, 0666);
			if (data->fd_outfiles == -1)
			{
				perror(strerror(errno));
				exit (errno);
			}
			i++;
		}
	}
}

void	ft_wait_her(void)
{
	int	status;

	if (waitpid(0, &status, 0) == -1)
	{
		perror("wait : error");
		exit (1);
	}
	if (WIFEXITED(status))
		g_glob.g_exit = status;
	else if (status == 2)
		g_glob.g_exit = 1;
}

void	ft_wait(t_exec_data *e_data)
{
	int	status;
	int	i;

	i = 0;
	while (i < e_data->nb_node)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			perror("wait : error");
			exit (1);
		}
		if (WEXITSTATUS(status))
			g_glob.g_exit = WEXITSTATUS(status);
		else if (WTERMSIG(status))
			g_glob.g_exit = 128 + status;
		else
			g_glob.g_exit = 0;
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
