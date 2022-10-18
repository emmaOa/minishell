/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:14:29 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/18 12:54:16 by iouazzan         ###   ########.fr       */
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
	if (count_args(arv) == 2)
		exit (0);
	valid_nb(arv[1]);
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

void	valid_nb(char *str)
{
	int	i;
 
	i = 0;
	if (ft_isdigit(str[0]) == 0 && (str[0] != '-' || str[0] != '+'))
		ft_exit("numeric argument required\n", 255);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			ft_exit("numeric argument required\n", 255);
		i++;
	}
}