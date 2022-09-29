/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:46:59 by iouazzan          #+#    #+#             */
/*   Updated: 2021/11/26 01:17:41 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	size_t	i;

	s = (char *)str;
	i = ft_strlen(str) + 1;
	while (i--)
	{
		if (s[i] == (char)c)
			return (s + i);
	}
	return (NULL);
}