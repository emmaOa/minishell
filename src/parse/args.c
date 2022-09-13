/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:27:54 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/31 14:01:51 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int len_2d_array(void **array)
{
    int i;
    
    i = 0;
	if(!array)
		return (0);
    while (array[i])
        i++;
    return (i);
}

// char *last_arg(t_list *exec)
// {
// 	int i;
// 	char **ar;

// 	i = 0;
// 	if (((t_data *)exec->content)->args)

// }

void    fill_args(t_list *exec,t_token *token, t_lexer *lexer)
{
    char	*arg;
	(void)lexer;
	if(((t_data *)exec->content)->error != 1)
	{
		token->i++;
		arg = ft_strdup("");
		if(check_qaout(token->value))
			qaout(exec,token->value, &arg,0);
		else if(check_if_expand(token->value))
		{
			expand(exec,token->value,&arg);
			expand_split(exec,arg);
			return;
		}
		else
		{
    		arg = ft_strdup(token->value);
			printf("%s\n", arg);
			if (lexer->here_doc == 2)
				((t_data *)exec->content)->delimiter = arg;
		}
		((t_data *)exec->content)->args = (char **)ft_2d_realloc((void **)(((t_data *)exec->content)->args),len_2d_array((void **)(((t_data *)exec->content)->args)) + 1);
		((t_data *)exec->content)->args[len_2d_array((void **)(((t_data *)exec->content)->args))] = arg;	
	}
}

void **ft_2d_realloc(void **arg,int size)
{
    void **new;
    int j;
    
    j = 0;
    new = (void **)malloc(sizeof(void *) * (size + 1));
    if(arg)
	{
		while (arg[j])
    	{
    	    new[j] = ft_strdup(arg[j]);
    	    j++;
    	}
	}
    new[j] = NULL;
	new[j + 1] = NULL;
	free(arg);//free 2d array
    return (new);
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
