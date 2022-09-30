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
		ft_exit_bonus("path not founde: ");
	i = 0;
	while (tmp[i] && tmp[i] != '=')
	{
		tmp[i] = tmp[i + 1];
		i++;
	}
	return (tmp);
}

char	*ft_url(char *path, t_list *exec)
{
	int		i;
	char	**url;
	char	*cmd_path;

	i = 0;
	if (ft_strchr(((t_data *)exec->content)->args[0], '/'))
	{
		if (access(((t_data *)exec->content)->args[0], F_OK) == 0)
			return (((t_data *)exec->content)->args[0]);
		return (NULL);
	}
	url = ft_split(path, ':');
	while (url[i])
	{
		cmd_path = ft_strjoin(ft_strdup(url[i]), "/");
		cmd_path = ft_strjoin(cmd_path, ((t_data *)exec->content)->args[0]);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
