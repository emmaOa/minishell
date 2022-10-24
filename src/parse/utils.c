/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouazzan <iouazzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:53:37 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/10/23 20:04:29 by iouazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

char	*ft_join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_join1(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	free(s1);
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	free(s2);
	str[i + j] = '\0';
	return (str);
}

void	fill_outfile(t_list *exec, t_token *token)
{
	((t_data *)exec->content)->outfiles = (char **)ft_2d_realloc \
	((void **)(((t_data *)exec->content)->outfiles), \
	len_2d_array((void **)(((t_data *)exec->content)->outfiles)) + 1);
	((t_data *)exec->content)->outfiles[len_2d_array \
	((void **)(((t_data *)exec->content)->outfiles))] = ft_strdup(token->value);
}
