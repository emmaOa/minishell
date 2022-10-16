/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:00:22 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/17 00:39:12 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	ft_pipe(t_exec_data *data)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	data->fd_pipe = (int **)malloc((data->nb_node + 1) * sizeof(int *));
	while (x < data->nb_node)
	{
		data->fd_pipe[x] = (int *)malloc(2 * sizeof(int));
		x++;
	}
	while (i < data->nb_node)
	{
		if (pipe(data->fd_pipe[i]) == -1)
			ft_exit("error: pipe failed\n", 1);
		i++;
	}
	return (0);
}
