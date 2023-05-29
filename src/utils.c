/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:06:34 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/16 16:54:23 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_whitespace(const unsigned char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ft_is_end_of_word(const unsigned char c)
{
	return (c == '>' || c == '<' || c == '|' \
			|| ft_is_whitespace(c) || c == '\0');
}

int	ft_is_path(char *path)
{
	return (ft_strchr((const char *)path, '/') != 0);
}

int	ft_is_exit(const char *str)
{
	while (ft_is_whitespace(*str))
		str++;
	if (ft_strncmp(str, "exit", 4) == 0)
	{
		str += 4;
		while (ft_is_whitespace(*str))
			str++;
		if (!*str)
			return (1);
	}
	return (0);
}

int	ft_isnumeric(const char *str)
{
	while (ft_is_whitespace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (ft_isdigit(*str))
		str++;
	while (ft_is_whitespace(*str))
		str++;
	return (!*str);
}

// char	*ft_unsplit(const char **matrix, const char c)
// {
// 	char	*str;
// 	char	*tmp;
// 	size_t	i;

// 	str = (char *)malloc(sizeof(char));
// 	str[0] = '\0';
// 	i = 0;
// 	while (matrix[i])
// 	{
// 		tmp = ft_strjoin(str, matrix[i]);
// 		free(str);
// 		if (matrix[i + 1])
// 		{
// 			str = ft_strjoin(tmp, &c);
// 			free(tmp);
// 		}
// 		else
// 		{
// 			str = ft_strdup(tmp);
// 			free(tmp);
// 		}
// 		i++;
// 	}
// 	return (str);
// }
