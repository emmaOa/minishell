#include"../../include/minishell.h"

int ft_cd(t_list *exec, t_exec_data *e_data)
{
    char **arv;
   	char buf[1000];
    char *cur_pwd;

    errno = 0;
    e_data->pwd = getcwd(buf, sizeof(buf));
    cur_pwd = ft_strjoin(e_data->pwd, "/");
    arv = ((t_data *)exec->content)->args;
    if (nb_arv(arv) <= 2)
    {
        if (nb_arv(arv) == 1 || ft_strncmp(arv[1], "~", ft_strlen(arv[1])) == 0)
        {
            chdir(check_home(exec));
        }
        else
        {
            ft_pwd();
            cur_pwd = ft_strjoin(cur_pwd, arv[1]);
            chdir(cur_pwd);
            ft_pwd();
        }
    }
    else
        printf("minishell: cd: too many arguments\n");
    if (errno != 0)
        printf("minishell cd: %s: %s\n", arv[1], strerror(errno));
    return (0);
}