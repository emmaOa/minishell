/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:46:55 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/24 00:09:09 by omeslall         ###   ########.fr       */
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
		if(((t_data *)exec->content)->infiles)
		{
			printf("-----------------infiles-------------------------\n");
			while(((t_data *)exec->content)->n_infiles > i)
			{
					printf("---((t_data *)exec->content)->infiles[%d]--->%d\n",i,((t_data *)exec->content)->infiles[i]);
					printf("---((t_data *)exec->content)->inf--->%s\n",((t_data *)exec->content)->inf);
				i++;
			}
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
					printf("---((t_data *)exec->content)->append[%d]--->%s\n",i,((t_data *)exec->content)->append[i]);
				i++;
			}
			printf("-----------------append-------------------------\n");
				
		}
		i = 0;
		if(((t_data *)exec->content)->hd)
		{
			printf("-----------------hd-------------------------\n");
			while(((t_data *)exec->content)->hd[i])
			{
					printf("---((t_data *)exec->content)->hd[%d]--->%s\n",i,((t_data *)exec->content)->hd[i]);
				i++;
			}
			printf("-----------------hd-------------------------\n");
				
		}
		printf("========================================================================================\n");
		exec = exec->next;
	}
}

int	count_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i + 1);
}

void	util_token(t_token **token, t_list *exec, t_lexer *lexer)
{
	if ((*token)->e_type == ARG)
		fill_args(ft_lstlast(exec), *token);
	else if ((*token)->e_type == L_REDIRECTION
		|| (*token)->e_type == R_REDIRECTION)
		fill_redirections(ft_lstlast(exec), token, lexer);
	else if ((*token)->e_type == PIPE)
		fill_pipe(exec);
}

int	norm1(t_list *exec, char **value, int i)
{
	((t_data *)(exec->content))->if_hd = 1;
	if (check_qaout(((t_data *)exec->content)->hd[i]) == 1)
		single_quote(((t_data *)exec->content)->hd[i], value, 0);
	else if (check_qaout(((t_data *)exec->content)->hd[i]) == 2)
		double_quote(exec, ((t_data *)exec->content)->hd[i], value, 0);
	((t_data *)(exec->content))->if_hd = 0;
	return (0);
}

int	check_inf(int *infiles, int len, int nb_node, t_exec_data *e_data)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (infiles[i] == -1)
			return (infiles[i]);
		i++;
	}
	if (e_data->fd_her[nb_node] != -2)
		return (e_data->fd_her[nb_node]);
	return (infiles[len - 1]);
}

int	parse(char *line, t_exec_data *e_data)
{
	t_token	*token;
	t_lexer	*lexer;
	t_list	*exec;

	if (!handle_errors(line))
		return (0);
	lexer = init_lexer(line);
	token = get_next_token(lexer);
	exec = init_execution();
	while (token)
	{
		util_token(&token, exec, lexer);
		free_token(token);
		token = get_next_token(lexer);
	}
	printer(exec);
	exec_herdoc(exec, e_data);
	list(e_data, exec);
	free(lexer);
	free_exec(exec);
	// system("leaks minishell");
	return (0);
}
