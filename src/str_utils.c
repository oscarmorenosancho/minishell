/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:04:41 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/24 15:59:44 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-(int)*s2);
	else if (!s2)
		return ((int)*s1);
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((int)*s1 - (int)*s2);
}

void	ft_stradd_str(char **s1, const char *s2)
{
	char	*tmp;

	if (!s2)
		return ;
	if (!*s1)
		*s1 = ft_calloc(1, sizeof(char));
	tmp = ft_strjoin(*s1, s2);
	ft_free((void **)s1);
	*s1 = tmp;
}

void	ft_stradd_char(char **s1, char c)
{
	char	*tmp;
	char	*pointer_c;

	pointer_c = (char *)malloc(sizeof(char) * 2);
	if (!pointer_c)
		return ;
	pointer_c[0] = c;
	pointer_c[1] = '\0';
	if (!*s1)
	{
		*s1 = ft_strdup(pointer_c);
		free(pointer_c);
		return ;
	}
	tmp = ft_strjoin(*s1, pointer_c);
	free(pointer_c);
	ft_free((void **)s1);
	*s1 = ft_strdup(tmp);
	free(tmp);
}

char	ft_get_last_char(char *str)
{
	size_t	length;

	if (!str)
		return ('\0');
	length = ft_strlen_safe(str);
	if (length == 0)
		return ('\0');
	return (str[length - 1]);
}
