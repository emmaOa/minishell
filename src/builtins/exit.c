/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:14:29 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/18 12:10:29 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	ft_exit_builtin(char **arv)
{
	int	i;
	int	j;
	int	nb;

	i = 1;
	j = 0;
	if (g_glob.child == 1)
		return ;
	while (arv[i][j])
	{
		if (ft_isdigit(arv[i][j]) == 0
			&& arv[i][j] != '-' && arv[i][j] != '+')
			ft_exit("numeric argument required\n", 255);
		j++;
	}
	if (count_args(arv) > 3)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	nb = ft_atoi(arv[1]);
	if (nb > 2147483647)
		exit (0);
	exit (nb % 256);
}
