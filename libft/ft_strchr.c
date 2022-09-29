/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:59:53 by iouazzan          #+#    #+#             */
/*   Updated: 2021/11/25 21:13:07 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*s;
	int		len;

	s = (char *)str;
	len = ft_strlen(s) + 1;
	while (len--)
	{
		if (*s++ == (char)c)
			return (s - 1);
	}
	return (NULL);
}
