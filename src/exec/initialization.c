/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:02:51 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/17 19:38:01 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	init_e_data(t_exec_data *e_data, char **envp)
{
	e_data->pwd = val_env(envp);
	e_data->url = NULL;
	e_data->fd_her = NULL;
	e_data->nb_node = 0;
}

void	init_global(void)
{
	g_glob.child = 0;
	g_glob.fd_built = 1;
	g_glob.expand_hd = 0;
	g_glob.g_exit = 0;
}

void	init_in_out(t_exec_data *e_data)
{
	e_data->infile = -2;
	e_data->fd_outfiles = -2;
}

void	int_main(char **envp, t_exec_data *e_data)
{
	g_glob.g_exit = 0;
	init_e_data(e_data, envp);
	arr_to_list(e_data, envp);
	g_glob.head_env = e_data->head_env;
	sig_main();
}
