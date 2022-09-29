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
					printf("---((t_data *)exec->content)->inf[%d]--->%s\n",i,((t_data *)exec->content)->inf);
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

char	*parse_limiter(char *str, int *expand)
{
	char	q;
	char	*new;
	char	*tmp;
	int		i;
	int		start;

	i = -1;
	new = ft_calloc(1, sizeof(char));
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			(*expand) = 0;
			start = i + 1;
			q = str[i];
			while (str[++(i)] && str[i] != q)
				;
			tmp = ft_substr2(str, start, i - start);
		}
		else
			tmp = ft_substr2(str, i, 1);
		new = ft_join(new, tmp);
		free(tmp);
	}
	return (new);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r' || c == '\0')
		return (1);
	return (0);
}

int	is_acceptable(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

char	*get_variable_name(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * get_char_index(str, '=') + 1);
	if (!tmp)
		return (NULL);
	while (++i < get_char_index(str, '='))
		tmp[i] = str[i];
	tmp[i] = 0;
	return (tmp);
}

int	get_char_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (0);
}

char	*expand_dollar(char *str, char **env)
{
	int		i;
	int		len;
	int		slen;
	int		tlen;
	char	*tmp;

	i = -1;
	slen = ft_strlen(str);
	while (env[++i])
	{
		tmp = get_variable_name(env[i]);
		if (!tmp)
			return (NULL);
		tlen = ft_strlen(tmp);
		len = ((tlen >= slen) * tlen) + ((tlen < slen) * slen);
		if (ft_strncmp(tmp, str, len) == 0)
		{
			free(tmp);
			return (ft_strdup(env[i] + get_char_index(env[i], '=') + 1));
		}
		free(tmp);
	}
	return (NULL);
}

char	*new_value(char *str, int i, int start)
{
	char	*tmp;
	char	*new;

	tmp = ft_substr2(str, start, i - start);
	if (!tmp[0])
	{
		free(tmp);
		return (NULL);
	}
	else
		new = expand_dollar(tmp, g_glob.envp);
	free(tmp);
	return (new);
}

char	*parse_dollar(char *str, int *i, int quote)
{
	int		start;
	char	*new;

	start = *i + 1;
	g_glob.dollar = 1;
	if (str[start] == '?')
	{
		new = ft_itoa(g_glob.g_exit_status);
		(*i)++;
	}
	else if ((str[start] == '"' || str[start] == '\'') && !quote)
		return (NULL);
	else if (is_separator(str[start]) || !is_acceptable(str[start]))
		new = ft_strdup("$");
	else
	{
		while (str[*i] && is_acceptable(str[++(*i)]))
			;
		new = new_value(str, *i, start);
		(*i)--;
	}
	return (new);
}

char	*parse_buff(char *buff)
{
	int		i;
	char	*new;
	char	*tmp;

	i = -1;
	new = ft_calloc(1, sizeof(char));
	while (buff[++i])
	{
		if (buff[i] == '$')
			tmp = parse_dollar(buff, &i, 1);
		else
			tmp = ft_substr2(buff, i, 1);
		new = ft_join(new, tmp);
		free(tmp);
	}
	free (buff);
	return (new);
}

int	check_inf(int *infiles, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (infiles[i] == -1)
			return (infiles[i]);
		i++;
	}
	return (infiles[len - 1]);
}

void 	here_d(char *delimiter, t_exec_data *e_data)
{
	char *line;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(delimiter, line) == 0 || !line)
			exit(0);
		else
		{
			if (line)
			{
				ft_putstr_fd(line, e_data->fd_her);
				ft_putstr_fd("\n", e_data->fd_her);
				free(line);
			}
		}
	}
}

int exec_herdoc(t_list *exec, t_exec_data *e_data)
{
	int i;
	int id_fork;
	t_list *node;

	node = exec;
	while (node)
	{
		i = 0;
		if (((t_data *)node->content)->hd)
		{
			while (((t_data *)node->content)->hd[i])
			{
				id_fork = fork();
				if (id_fork == -1)
					ft_exit_bonus("error: failed in fork herdoc");
				e_data->fd_her = open(((t_data *)node->content)->hd[i], O_CREAT | O_RDWR , 0644);
				if (e_data->fd_her == -1)
				{
					((t_data *)exec->content)->inf = ft_strdup(((t_data *)node->content)->hd[i]);
					((t_data *)exec->content)->error = 1;
				}
				g_glob.child = 1;
				if (id_fork == 0)
					here_d(((t_data *)node->content)->hd[i], e_data);
				wait(NULL);
				g_glob.child = 0;
				signal(SIGQUIT,SIG_IGN);
				signal(SIGINT,sig_handler);
				if (e_data->infile != -1)
					e_data->infile = e_data->fd_her;
				i++;
			}
		}
		node = node->next;
	}
	return (0);
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

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*tmp;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int	parse(char *line, char **envp, t_exec_data *e_data)
{
	t_token	*token;
	t_lexer	*lexer;
	t_list	*exec;
	(void)e_data;

	if (!handle_errors(line))
		return (0);
	lexer = init_lexer(line);
	token = get_next_token(lexer);
	exec = init_execution(envp);
	while (token)
	{
		if (token->type == ARG)
			fill_args(ft_lstlast(exec), token);
		else if (token->type == L_REDIRECTION || token->type == R_REDIRECTION)
			fill_redirections(ft_lstlast(exec), &token, lexer);
		else if (token->type == PIPE)
			fill_pipe(exec, envp);
		free_token(token);
		token = get_next_token(lexer);
	}
	if (((t_data *)exec->content)->infiles)
		e_data->infile = check_inf(((t_data *)exec->content)->infiles, ((t_data *)exec->content)->n_infiles);
	printer(exec);
	e_data->nb_node = ft_lstsize(exec);
	exec_herdoc(exec, e_data);
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
			g_glob.child = 1;
			if (e_data->forck == 0)
				mult_pipe(e_data, exec);
			e_data->i++;
			exec = exec->next;
		}
		ft_close(e_data);
		free_bonus_int(e_data->fd_pipe, 0, e_data->nb_node);
		ft_wait(e_data);

	}
	free(lexer);
	free_exec(exec);
	// system("leaks minishell");
	return (0);
}
