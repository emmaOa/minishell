/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arry_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:13 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/23 18:24:11 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	arr_to_list(t_exec_data *data, char *str[])
{
	int			i;
	t_env_list	*tmp;

	i = 0;
	data->head_env = NULL;
	while (str[i])
	{
		tmp = malloc(sizeof(t_env_list));
		tmp->key = key_evn(str[i]);
		tmp->cont = cont_evn(str[i]);
		tmp->next = NULL;
		lstadd_back(&data->head_env, tmp);
		i++;
	}
}

void	with_cont(t_exec_data *data, char *str)
{
	t_env_list	*tmp;

	tmp = malloc(sizeof(t_env_list));
	tmp->key = key_evn(str);
	tmp->cont = cont_evn(str);
	tmp->next = NULL;
	lstadd_back(&data->arv_list, tmp);
}

void	without_cont(t_exec_data *data, char *str)
{
	t_env_list	*tmp;

	if (check_valid_enva_jout(str) == 0)
	{
		tmp = malloc(sizeof(t_env_list));
		tmp->key = ft_strdup(str);
		tmp->cont = NULL;
		tmp->next = NULL;
		lstadd_back(&data->key_without_cont, tmp);
	}
	else
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" : not a valid identifier\n", 2);
		g_glob.g_exit = 1;
	}
}

void	arv_to_list(t_exec_data *data, char *str[])
{
	int	i;

	i = 0;
	data->arv_list = NULL;
	data->key_without_cont = NULL;
	if (str)
	{
		while (str[i])
		{
			if (check_equal(str[i], i) == 1)
				with_cont(data, str[i]);
			else if (check_equal(str[i], i) == 0)
				without_cont(data, str[i]);
			i++;
		}
	}
}
