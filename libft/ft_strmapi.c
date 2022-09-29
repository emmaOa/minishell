/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 21:56:03 by iouazzan          #+#    #+#             */
/*   Updated: 2021/11/25 21:58:39 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*sub;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	sub = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (s[i])
	{
		sub[i] = (*f)(i, s[i]);
		i++;
	}
	sub[i] = '\0';
	return (sub);
}