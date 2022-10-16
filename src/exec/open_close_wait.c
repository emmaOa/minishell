/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_wait.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:00:17 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/17 00:26:41 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	ft_open_outfiles(t_exec_data *data, t_list *exec)
{
	char	**name_files;

	if (((t_data *)exec->content)->append)
		ft_append(data, exec);
	else
	{
		name_files = ((t_data *)exec->content)->outfiles;
		if (name_files)
			open_outfile_utl(name_files, data);
	}
	return (0);
}

void	open_outfile_utl(char **name_files, t_exec_data *data)
{
	int	i;

	i = 0;
	while (i < count_args(name_files) - 1)
	{
		data->fd_outfiles = open
			(name_files[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (data->fd_outfiles == -1)
		{
			if (g_glob.child == 0)
			{
				g_glob.g_exit = 1;
				printf("open outfile failed\n");
				return ;
			}
			ft_exit("open outfile failed\n", 1);
		}
		i++;
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
