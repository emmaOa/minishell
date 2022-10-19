/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:58:12 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/19 13:37:16 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	exec_builtins_utl(t_list *exec, t_exec_data *e_data, char **arv)
{
	if (ft_strcmp(e_data->name_built, "echo") == 0)
		ft_echo(arv);
	else if (ft_strcmp(arv[0], "pwd") == 0)
		ft_pwd(e_data);
	else if (ft_strcmp(arv[0], "export") == 0)
	{
		e_data->arv_list = arv_to_list(e_data, arv);
		ft_export(e_data);
		lstclear(&e_data->arv_list);
		lstclear(&e_data->key_without_cont);
	}
	else if (ft_strcmp(arv[0], "unset") == 0)
		ft_unset(e_data, exec);
	else if (ft_strcmp(arv[0], "env") == 0)
		ft_env(e_data, exec);
	else if (ft_strcmp(arv[0], "exit") == 0)
		ft_exit_builtin(arv);
	else if (ft_strcmp(arv[0], "cd") == 0)
		ft_cd(exec, e_data);
	if (g_glob.child == 1)
		exit(0);
}

int	exec_builtins(t_list *exec, t_exec_data *e_data)
{
	char	**arv;

	arv = NULL;
	if (((t_data *)exec->content)->args)
	{
		arv = ((t_data *)exec->content)->args;
		exec_builtins_utl(exec, e_data, arv);
	}
	return (0);
}
