#include"../../include/minishell.h"

int	ft_pwd(t_exec_data *data)
{
	char	buf[1000];

	if (getcwd(buf, sizeof(buf)))
		printf("%s\n", buf);
	else
		printf("my -->%s\n", data->pwd);
	return (0);
}
