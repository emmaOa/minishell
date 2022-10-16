/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   url_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:00:33 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/15 21:48:13 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

char	*ft_path(char *env[])
{
	int		i;
	char	*pt;
	char	*tmp;

	i = 0;
	tmp = NULL;
	pt = "PATH";
	while (env[i])
	{
		if (ft_strncmp(env[i], pt, ft_strlen(pt)) == 0)
			tmp = env[i];
		i++;
	}
	if (!tmp)
		ft_exit("No such file or directory", 127);
	i = 0;
	return (ft_strchr(tmp, '=') + 1);
}

char	*url_2(char *arg)
{
	if (access(arg, F_OK) == 0)
		return (arg);
	return (NULL);
}

char	*ft_url(char *path, t_list *exec)
{
	int		i;
	char	**url;
	char	*cmd_path;

	i = 0;
	if (ft_strchr(((t_data *)exec->content)->args[0], '/'))
		return (url_2(((t_data *)exec->content)->args[0]));
	url = ft_split(path, ':');
	while (url[i])
	{
		cmd_path = ft_strjoin(ft_strdup(url[i]), "/");
		cmd_path = ft_strjoin(cmd_path, ((t_data *)exec->content)->args[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free_2d_array(url);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_2d_array(url);
	return (NULL);
}
