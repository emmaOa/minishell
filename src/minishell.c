/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:50:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/10/11 14:36:10 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	init_e_data(t_exec_data *e_data)
{
	e_data->url = NULL;
	e_data->fd_her = NULL;
	e_data->nb_node = 0;
}

void	init_global(void)
{
	g_glob.child = 0;
	g_glob.fd_built = 1;
	g_glob.expand_hd = 0;
}

void	init_in_out(t_exec_data *e_data)
{
	e_data->infile = -2;
	e_data->fd_outfiles = -2;
}

void	check_line(char *line, t_exec_data *e_data)
{
	if (line && *line)
		add_history (line);
	if (*line)
		parse(line, e_data);
}

int	main(int ac, char **av, char **envp)
{
	t_exec_data	*e_data;
	char		*line;

	if (!av || !envp)
		return (0);
	errno = 0;
	if (ac == 1)
	{
		e_data = malloc(sizeof(t_exec_data));
		init_e_data(e_data);
		arr_to_list(e_data, envp);
		g_glob.head_env = e_data->head_env;
		sig_main();
		while (1337)
		{
			init_global();
			init_in_out(e_data);
			line = readline("minishell:");
			if (!line)
				break ;
			check_line(line, e_data);
		}
		free(e_data);
	}
	// system("leaks minishell");
	return (errno);
}
