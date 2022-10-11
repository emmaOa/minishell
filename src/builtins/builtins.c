/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:58:12 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/10 17:58:14 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	exec_builtins_utl(t_list *exec, t_exec_data *e_data, char **arv)
{
	if (ft_strncmp(e_data->name_built, "echo", ft_strlen("echo")) == 0)
		ft_echo(arv);
	else if (ft_strncmp(arv[0], "pwd", ft_strlen("pwd")) == 0)
		ft_pwd(e_data);
	else if (ft_strncmp(arv[0], "export", ft_strlen("export")) == 0)
	{
		e_data->arv_list = arv_to_list(e_data, arv);
		ft_export(e_data);
	}
	else if (ft_strncmp(arv[0], "unset", ft_strlen("unset")) == 0)
	{
		arv_unset(e_data, ((t_data *)exec->content)->args);
		ft_unset(e_data);
	}
	else if (ft_strncmp(arv[0], "env", ft_strlen("env")) == 0)
		ft_env(e_data);
	else if (ft_strncmp(arv[0], "exit", ft_strlen("exit")) == 0)
		exit(0);
	else if (ft_strncmp(arv[0], "cd", ft_strlen("cd")) == 0)
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
