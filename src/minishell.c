/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:50:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/24 13:54:47 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	g_exit_status;

int main(int ac,char **av,char **envp)
{
	char *line;

	t_exec_data *e_data;

	if (!av || !envp)
		return(0);
	errno = 0;
	if (ac == 1)
	{
		e_data = malloc(sizeof(t_exec_data));
		e_data->pwd = val_env(envp);
		e_data->url = NULL;
		e_data->fd_outfiles = -2;
		e_data->infile = -2;
		g_glob.child = 0;
		e_data->ev = NULL;
		arr_to_list(e_data, envp);
		sig_main();
		while(1337)
		{	
			line = readline("minishell:");
			if (!line)
				break;
			if (line && *line)
				add_history (line);
			if(*line)
				parse(line, envp, e_data);
			// sig_main();
		}
	}
	return(errno);
}