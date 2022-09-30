#include"../../include/minishell.h"

void	exec_cmd(t_list *exec)
{
	char	*url;

	
	url = ft_url(ft_path(g_glob.envp), exec);
	ft_putstr_fd(url, 2);
	if (url == NULL)
		ft_exit_bonus("command not founde");
	if (execve(url, ((t_data *)exec->content)->args, g_glob.envp) < 0)
		ft_exit_bonus("command not execute");
}

void ft_p(char **str)
{
	int i = 0;

	while (str[i])
	{
		printf("------>: %s <------\n", str[i]);
		i++;
	}
}

void	free_bonus_int(int **tabl, int start, int len)
{
	while (start < len)
	{
		free(tabl[start]);
		start++;
	}
	free(tabl);
}

void	ft_free_int(int **tabl, int start, int len)
{
	while (start < len)
	{
		free(tabl[start]);
		start++;
	}
	free(tabl);
}

void	ft_exit_bonus(char *s)
{
	perror(s);
	exit(0);
}
