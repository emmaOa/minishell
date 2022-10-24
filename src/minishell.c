/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:50:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/10/24 01:29:13 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

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

	if (!av || !envp || !envp[0])
		return (0);
	if (ac == 1)
	{
		e_data = malloc(sizeof(t_exec_data));
		int_main(envp, e_data);
		while (1337)
		{
			init_in_out(e_data);
			init_global(e_data);
			line = readline("minishell:");
			if (!line)
			{
				free (e_data->pwd);
				break ;
			}
			check_line(line, e_data);
			free(line);
		}
		free(e_data);
	}
	return (g_glob.g_exit);
}
