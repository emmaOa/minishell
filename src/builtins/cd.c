#include"../../include/minishell.h"

int	ft_cd(t_list *exec, t_exec_data *e_data)
{
	char	**arv;

	errno = 0;
	arv = ((t_data *)exec->content)->args;
	if (nb_arv(arv) <= 2)
		cd_utl(e_data, arv);
	else
		printf("minishell: cd: too many arguments\n");
	if (errno != 0)
		printf("minishell cd: %s: %s\n", arv[1], strerror(errno));
	return (0);
}

void	cd_utl(t_exec_data *e_data, char **arv)
{
	char	buf[1000];
	char	*cur_pwd;
	char	*new_pwd;

	cur_pwd = NULL;
	new_pwd = NULL;
	if (getcwd(buf, sizeof(buf)))
	{
		e_data->pwd = getcwd(buf, sizeof(buf));
		if (nb_arv(arv) == 1
			|| ft_strncmp(arv[1], "~", ft_strlen(arv[1])) == 0)
			chdir(check_home());
		else
		{
			cur_pwd = ft_strjoin(ft_strdup("/"), arv[1]);
			new_pwd = ft_strjoin(ft_strdup(buf), cur_pwd);
			e_data->pwd = ft_strjoin(ft_strdup(buf), cur_pwd);
			chdir(new_pwd);
		}
	}
	else
		my_pwd(e_data, arv);
}

void	my_pwd(t_exec_data *e_data, char **arv)
{
	char	*s;

	s = "cd: error retrieving current directory: getcwd: cannot access ";
	printf("%sparent directories: No such file or directory\n", s);
	e_data->pwd = ft_strjoin(ft_strdup(e_data->pwd), "/");
	e_data->pwd = ft_strjoin(ft_strdup(e_data->pwd), arv[1]);
}

int	check_trash(char *buf)
{
	char	**path;
	int		i;

	path = ft_split(buf, '/');
	i = 0;
	while (path[i])
	{
		if (ft_strncmp(path[i], ".Trash/", ft_strlen(path[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}
