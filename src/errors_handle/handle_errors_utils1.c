/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 03:05:33 by omeslall          #+#    #+#             */
/*   Updated: 2022/10/17 00:42:28 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	utils_handle_errors(char *argv, size_t *i, size_t *j)
{
	if (argv[*i] == '"' || argv[*i] == 39)
	{
		*j = *i + 1;
		while (argv[*j] != argv[*i])
			*j += 1;
		*i = *j;
	}
}

void	skip_in_qaout(char *argv, int *i)
{
	int	j;

	j = 0;
	if (argv[*i] == '"' || argv[*i] == 39)
	{
		j = *i + 1;
		while (argv[j] != argv[*i])
			j += 1;
		*i = j;
	}
}
