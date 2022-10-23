/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:26 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/22 18:18:07 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	exec_cmd(t_list *exec, t_exec_data *e_data)
{
	char	*url;
	char	**env;
	char	*cmd;

	cmd = NULL;
	env = list_to_arr(e_data->head_env);
	url = ft_url(ft_path(env), exec);
	if (url == NULL)
	{
		ft_putstr_fd(((t_data *)exec->content)->args[0], 2);
		ft_putstr_fd(":", 2);
		ft_exit("command not founde\n", 127);
	}
	if (execve(url, ((t_data *)exec->content)->args, env) < 0)
		ft_exit("command not executed\n", 1);
}

void	free_bonus_int(int **tabl, int start, int len)
{
	while (start < len)
	{
		free(tabl[start]);
		start++;
	}
	free(tabl);
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

void	ft_exit(char *s, int nb)
{
	ft_putstr_fd(s, 2);
	exit(nb);
}
