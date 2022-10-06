/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:45:36 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/25 01:33:23 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

t_list	*init_execution()
{
	t_list	*exec;

	exec = malloc(sizeof(t_list));
	exec->content = init_data();
	exec->next = NULL;
	return (exec);
}

t_data	*init_data(void)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	data->args = NULL;
	data->error = 0;
	data->inf = NULL;
	data->infiles = NULL;
	data->n_infiles = 0;
	data->outfiles = NULL;
	data->append = NULL;
	data->hd = NULL;
	data->if_hd = 0;
	return (data);
}

int	*ft_int_realloc(int *array, int len)
{
	int	*new;
	int	i;

	i = 0;
	new = malloc(sizeof(int) * (len + 1));
	while (i < len)
	{
		new[i] = array[i];
		i++;
	}
	new[i] = 0;
	free(array);
	return (new);
}
