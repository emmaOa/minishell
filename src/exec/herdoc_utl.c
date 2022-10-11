/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:46:56 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/10 18:47:40 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

char	*random_name(void)
{
	char	*name;
	char	buff;
	int		i;
	int		fd;

	name = malloc(10);
	i = 0;
	buff = '\0';
	fd = open("/dev/random", O_RDWR);
	while (i < 9)
	{
		read(fd, &buff, 1);
		if (buff >= 97 && buff <= 122)
		{
			name[i] = buff;
			i++;
		}
	}
	name[9] = 0;
	return (name);
}

char	*ft_ex_hd(char *line, t_exec_data *e_data)
{
	t_env_list	*env;

	env = e_data->head_env;
	while (env)
	{
		if (ft_strcmp((line + 1), env->key) == 0)
			return (env->cont);
		env = env->next;
	}
	return ("");
}

int	check_exp(char *line)
{
	if (ft_strlen(line) != 1)
	{
		if (line[0] == '$' && (line[1] != '\'' && line[1] != '"'))
			return (1);
		else
			return (0);
	}
	return (0);
}
