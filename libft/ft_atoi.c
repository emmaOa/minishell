/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:26:45 by iouazzan          #+#    #+#             */
/*   Updated: 2022/10/18 11:51:59 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

long long	ft_atoi(const char *str)
{
	int			i;
	long		count;
	long long	nbr;

	i = 0;
	count = 1;
	nbr = 0;
	while (str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		count = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		nbr = (str[i] - '0') + (nbr * 10);
		i++;
	}
	return (nbr * count);
}
