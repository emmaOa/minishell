#include"../../include/minishell.h"

int	ft_pwd(t_exec_data *data)
{
	char	buf[1000];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putstr_fd(buf, g_glob.fd_built);
		ft_putstr_fd("\n", g_glob.fd_built);
	}
	else
	{
		ft_putstr_fd(data->pwd, g_glob.fd_built);
		ft_putstr_fd("\n", g_glob.fd_built);
	}
	return (0);
}
