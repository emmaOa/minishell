/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:59:20 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/17 00:34:30 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

char	*key_evn(char *str)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	len = i;
	key = malloc(len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = str[i];
		i++;
	}
	key[len] = '\0';
	return (key);
}

char	*cont_evn(char *env)
{
	int		i;
	int		j;
	char	*cont;

	i = 0;
	j = 0;
	cont = malloc(ft_strlen(env));
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] != '=' || env[i + 1] == '\0')
		cont[j] = '\0';
	else
	{
		i++;
		while (env[i])
		{
			cont[j] = env[i];
			i++;
			j++;
		}
		cont[j] = '\0';
	}
	return (cont);
}

void	lstclear(t_env_list **lst)
{
	t_env_list	*temp;

	while (*lst != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free(temp);
	}
}

void	ft_append(t_exec_data *data, t_list *exec)
{
	int		i;
	char	**name_files;

	i = 0;
	name_files = ((t_data *)exec->content)->append;
	if (name_files)
	{
		while (i < count_args(name_files) - 1)
		{
			data->fd_outfiles = open
				(name_files[i], O_CREAT | O_RDWR | O_APPEND, 0666);
			if (data->fd_outfiles == -1)
			{
				if (g_glob.child == 0)
				{
					g_glob.g_exit = 1;
					printf("open append failed\n");
					return ;
				}
				ft_exit("open append failed\n", 1);
			}
			i++;
		}
	}
}
