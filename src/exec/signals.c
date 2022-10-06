#include"../../include/minishell.h"

void sig_main(void)
{
	// printf("ll\n");
	signal(SIGQUIT,SIG_IGN);
	signal(SIGINT,sig_handler);
}

void sig_child(void)
{
	// printf("jj\n");
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
void sig_handler(int signum)
{
	(void)signum;
	if (g_glob.child == 0)
	{
		ft_putstr_fd("\n", 1);
    	rl_on_new_line();
    	rl_replace_line("", 0);
    	rl_redisplay();
	}
	else
		ft_putstr_fd("\n", 2);
}
