/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   url_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:00:33 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/23 16:44:11 by iouazzan         ###   ########.fr       */
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
		return (NULL);
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

	i = -1;
	errno = 0;
	if ((ft_strchr(((t_data *)exec->content)->args[0], '/') && access
			(((t_data *)exec->content)->args[0], F_OK | X_OK) == -1) || !path)
		return (access_file(((t_data *)exec->content)->args[0]));
	else if (ft_strchr(((t_data *)exec->content)->args[0], '/'))
		return (url_2(((t_data *)exec->content)->args[0]));
	url = ft_split(path, ':');
	while (url[++i])
	{
		cmd_path = ft_strjoin(ft_strdup(url[i]), "/");
		cmd_path = ft_strjoin(cmd_path, ((t_data *)exec->content)->args[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free_2d_array(url);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_2d_array(url);
	return (NULL);
}

char	*access_file(char *str)
{
	if (access(str, F_OK | X_OK) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		if (errno == 20)
			exit (126);
		else
			exit (127);
	}
	return (url_2(str));
}
