/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:58:30 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/18 11:09:52 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec_data	*is_builtins(t_list *exec, t_exec_data *e_data)
{
	char	**arv;

	if (((t_data *)exec->content)->args)
	{
		arv = ((t_data *)exec->content)->args;
		e_data->nb_arv = nb_arv(arv);
		e_data->name_built = NULL;
		if ((ft_strcmp(arv[0], "echo") == 0)
			|| (ft_strcmp(arv[0], "pwd") == 0)
			|| (ft_strcmp(arv[0], "export") == 0)
			|| (ft_strcmp(arv[0], "env") == 0)
			|| (ft_strcmp(arv[0], "exit") == 0)
			|| (ft_strcmp(arv[0], "unset") == 0)
			|| (ft_strcmp(arv[0], "cd") == 0))
				e_data->name_built = arv[0];
	}
	return (e_data);
}
