/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:00:11 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/23 18:24:15 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	lstadd_back_plus(t_env_list **lst, t_env_list *new)
{
	t_env_list	*tmp;

	if (!new)
		return ;
	while (new)
	{
		if (just_equals(*lst, new) == 0)
		{
			tmp = malloc(sizeof(t_env_list));
			tmp->key = ft_strdup(new->key);
			tmp->cont = ft_strdup(new->cont);
			tmp->next = NULL;
			lstadd_back(lst, tmp);
		}
		new = new->next;
	}
}

void	lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*p;

	if (new == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	p = ft_lstlast_mini(*lst);
	p->next = new;
}

void	lstadd_back_export(t_exec_data *data)
{
	t_env_list	*arv;

	arv = data->arv_list;
	while (arv)
	{
		if (check_valid_enva_jout(arv->key) == 2)
		{
			if (plus_equals(data->head_env, arv) == 0)
				add_back_plus_equal(data, arv->cont, arv->key);
		}
		else if (check_valid_enva_jout(arv->key) == 0)
		{
			if (just_equals(data->head_env, arv) == 0)
				add_back_equal(data, arv->cont, arv->key);
		}
		else if (check_valid_enva_jout(arv->key) == 1)
		{
			ft_putstr_fd(arv->key, 2);
			ft_putstr_fd("=", 2);
			ft_putstr_fd(arv->cont, 2);
			ft_putstr_fd(" : not a valid identifier\n", 2);
			g_glob.g_exit = 1;
		}
		arv = arv->next;
	}
}

void	add_back_equal(t_exec_data *data, char *cont, char *key)
{
	t_env_list	*tmp;

	tmp = NULL;
	tmp = malloc(sizeof(t_env_list));
	tmp->key = ft_strdup(key);
	tmp->cont = ft_strdup(cont);
	tmp->next = NULL;
	lstadd_back(&data->head_env, tmp);
}

void	add_back_plus_equal(t_exec_data *data, char *cont, char *key)
{
	t_env_list	*tmp;

	tmp = NULL;
	tmp = malloc(sizeof(t_env_list));
	tmp->key = ft_strndup(key, (ft_strlen(key) - 1));
	tmp->cont = ft_strdup(cont);
	tmp->next = NULL;
	lstadd_back(&data->head_env, tmp);
}
