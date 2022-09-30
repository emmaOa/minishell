/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:34:17 by iouazzan          #+#    #+#             */
/*   Updated: 2021/11/25 21:54:34 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	j;
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	if (n == 0)
		return (i);
	j = 0;
	printf("src %s \n", dest);
	while (src[j] != '\0' && j < n - 1)
	{
		printf("inside loop \n");
		dest[j] = src[j];
		j++;
		printf("inside loop2 \n");
	}
	dest[j] = '\0';
	return (i);
}
