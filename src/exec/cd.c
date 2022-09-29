#include"../../include/minishell.h"

int ft_cd(t_list *exec, t_exec_data *e_data)
{
    char **arv;
   	char buf[1000];
    char *cur_pwd;
    char *new_pwd;

    errno = 0;
    arv = ((t_data *)exec->content)->args;
    if (nb_arv(arv) <= 2)
    {
        if (getcwd(buf, sizeof(buf)))
        {
            e_data->pwd = getcwd(buf, sizeof(buf));
            if (nb_arv(arv) == 1 || ft_strncmp(arv[1], "~", ft_strlen(arv[1])) == 0)
                chdir(check_home());
            else
            {
                cur_pwd = ft_strjoin("/", arv[1]);
                new_pwd = ft_strjoin(buf, cur_pwd);
                e_data->pwd = ft_strjoin(buf, cur_pwd);
                chdir(new_pwd);
            }
        }
        else
        {
            printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
            e_data->pwd = ft_strjoin(e_data->pwd, "/");
            e_data->pwd = ft_strjoin(e_data->pwd, arv[1]);
            return (0);
        }
    }
    else
        printf("minishell: cd: too many arguments\n");
    if (errno != 0)
        printf("minishell cd: %s: %s\n", arv[1], strerror(errno));
    return (0);
}

int check_trash(char *buf)
{
    char **path;
    int i;

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