/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:46:55 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/30 22:30:30 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	printer(t_list *exec)
{
	int i;
	i = 0;
	while (exec)
	{	
		printf("========================================================================================\n\n");

		if(((t_data *)exec->content)->args)
		{
			i = 0;
			printf("-----------------args-------------------------\n");
			while(((t_data *)exec->content)->args[i])
			{
					printf("----((t_data *)exec->content)->args[%d]----------->%s\n",i,((t_data *)exec->content)->args[i]);
				i++;
			}
			printf("-----------------args-------------------------\n\n");
		}
		i = 0;
		if(((t_data *)exec->content)->infiles != -2)
		{
			printf("-----------------infiles-------------------------\n");
					printf("---((t_data *)exec->content)->infiles--->%d\n",((t_data *)exec->content)->infiles);
					printf("---((t_data *)exec->content)->inf[%d]--->%s\n",i,((t_data *)exec->content)->inf);
			printf("-----------------infiles-------------------------\n\n");
				
		}
		i = 0;
		if(((t_data *)exec->content)->outfiles)
		{
			printf("-----------------outfiles-------------------------\n");
			while(((t_data *)exec->content)->outfiles[i])
			{
					printf("---((t_data *)exec->content)->outfiles[%d]--->%s\n",i,((t_data *)exec->content)->outfiles[i]);
				i++;
			}
			printf("-----------------outfiles-------------------------\n");
				
		}
		i = 0;
		if(((t_data *)exec->content)->append)
		{
			printf("-----------------append-------------------------\n");
			while(((t_data *)exec->content)->append[i])
			{
					printf("---((t_data *)exec->content)->infiles[%d]--->%s\n",i,((t_data *)exec->content)->append[i]);
				i++;
			}
			printf("-----------------append-------------------------\n");
				
		}
		if(((t_data *)exec->content)->delimiter)
		{
			printf("-----------------delimiter-------------------------\n");
					printf("---((t_data *)exec->content)->delimiter--->%s\n",((t_data *)exec->content)->delimiter);
			printf("-----------------delimiter-------------------------\n");
				
		}
		if(((t_data *)exec->content)->error)
		{
			printf("-----------------error-------------------------\n");
					printf("---((t_data *)exec->content)->error--->%d\n",((t_data *)exec->content)->error);
			printf("-----------------error-------------------------\n");
				
		}
		printf("========================================================================================\n");
		// i = 0;
		// if(((t_data *)exec->content)->envp)
		// {
		// 	printf("-----------------env-------------------------\n");
		// 	while(((t_data *)exec->content)->envp[i])
		// 	{
		// 			printf("%s\n", ((t_data *)exec->content)->envp[i]);
		// 		i++;
		// 	}
		// 	printf("-----------------env-------------------------\n");
				
		// }
		exec = exec->next;
	}
}

extern int	g_exit_status;

void sig_handler(int signum)
{
	(void)signum;
  printf("\nminishell:");
}

int	parse(char *line, char **envp, t_exec_data *e_data)
{
	t_token *token;
	t_lexer *lexer;
	t_list	*exec;

	(void)e_data;
	if(!handle_errors(line))
		return(0);
	lexer = init_lexer(line);
	token = get_next_token(lexer);
	exec = init_execution(envp);
	while (token)
	{
		
		if(token->type == ARG)
				fill_args(ft_lstlast(exec), token, lexer);
		else if(token->type == L_REDIRECTION || token->type == R_REDIRECTION)
			fill_redirections(ft_lstlast(exec), &token, lexer);
		else if(token->type == PIPE)
			fill_pipe(exec, envp);
		else if(token->type == HERE_DOC)
			here_d(ft_lstlast(exec), &token, lexer);
		free_token(token);
		token = get_next_token(lexer);
	}
	((t_data *)exec->content)->delimiter = lexer->here_doc;
	printer(exec);
	e_data->nb_node = ft_lstsize(exec);
	e_data = is_builtins(exec, e_data);
	if (e_data->nb_node == 1 && e_data->name_built)
		exec_builtins(exec, e_data);
	else
	{
		ft_pipe(e_data);
		e_data->i = 0;
		while (exec)
		{
			e_data = is_builtins(exec, e_data);
			e_data->forck = fork();
			if (e_data->forck == -1)
				ft_exit_bonus("error: failed in fork");
			if (e_data->forck == 0)
				mult_pipe(e_data, exec);
			e_data->i++;
			exec = exec->next;
		}
		ft_close(e_data);
		free_bonus_int(e_data->fd_pipe, 0, e_data->nb_node);
		ft_wait(e_data);
	}

	return(0);
}