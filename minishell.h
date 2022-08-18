#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <time.h>
 #include <string.h>
# include "libft/libft.h"
# include <sys/time.h>
# include <stdlib.h>
#include <fcntl.h>

typedef struct s_data
{
	int		ac;
	char	**av;
	struct s_list_env
	{
		void			*content;
		struct s_list_env	*next;
	}	t_list_env;
}			t_data;

int	ft_list_env(t_data	*data, char *env[]);
int	ft_check_n_echo(char *str);
int	ft_echo(t_data *data);
int	ft_cd(t_data *data);
#endif