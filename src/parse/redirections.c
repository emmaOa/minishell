/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:33:34 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/13 18:56:22 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer)
{
	if ((*token)->type == L_REDIRECTION && ((t_data *)exec->content)->error != 1)
	{
		free_token(*token);
		*token = get_next_token(lexer);
		if((*token)->type == ARG && ((t_data *)exec->content)->error != 1)
			fill_infile(exec, *token);
		
	}
	else if ((*token)->type == R_REDIRECTION && ((t_data *)exec->content)->error != 1)
	{
		free_token(*token);
		*token = get_next_token(lexer);
		if((*token)->type == ARG && ((t_data *)exec->content)->error != 1)
			fill_outfile(exec, *token);
		else if((*token)->type == R_REDIRECTION )
		{
			free_token(*token);
			*token = get_next_token(lexer);
			fill_append(exec, *token);
		}
	}
}

void	here_d(t_list *exec, t_token **token, t_lexer *lexer)
{
	int	fd;
	char *delimiter;
	char *line;

	fd = open((*token)->value, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
	{
		((t_data *)exec->content)->inf = ft_strdup((*token)->value);
		((t_data *)exec->content)->error = 1;
	}
	free_token(*token);
	*token = get_next_token(lexer);
	if((*token)->type == ARG)
	{
		delimiter = (*token)->value;
		while (1)
		{
			ft_putstr_fd("> ", 1);
			line = readline("");
			if (ft_strncmp(delimiter, line, ft_strlen(line)) != 0)
			{
				ft_putstr_fd(line, fd);
				free(line);
			}
			else
				break;
		}
		if (((t_data *)exec->content)->infiles != -1)
			((t_data *)exec->content)->infiles = fd;
	}
}

void	fill_infile(t_list *exec, t_token *token)
{
	int	fd;
	
	fd = open(token->value, O_RDONLY);
	if (fd == -1)
	{
		((t_data *)exec->content)->inf = ft_strdup(token->value);
		((t_data *)exec->content)->error = 1;
	}
	if (((t_data *)exec->content)->infiles != -1)
		((t_data *)exec->content)->infiles = fd;
}

void	fill_outfile(t_list *exec, t_token *token)
{
	char *outfile;

	outfile = ft_strdup(token->value);
	((t_data *)exec->content)->outfiles = (char **)ft_2d_realloc((void **)(((t_data *)exec->content)->outfiles),len_2d_array((void **)(((t_data *)exec->content)->outfiles)) + 1);
	((t_data *)exec->content)->outfiles[len_2d_array((void **)(((t_data *)exec->content)->outfiles))] = outfile;
}

void	fill_append(t_list *exec, t_token *token)
{
	char *outfile;
		
	outfile = ft_strdup(token->value);
	((t_data *)exec->content)->append = (char **)ft_2d_realloc((void **)(((t_data *)exec->content)->append),len_2d_array((void **)(((t_data *)exec->content)->append)) + 1);
	((t_data *)exec->content)->append[len_2d_array((void **)(((t_data *)exec->content)->append))] = outfile;
}
