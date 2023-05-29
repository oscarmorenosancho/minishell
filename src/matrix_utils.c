/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:53:41 by edomingu          #+#    #+#             */
/*   Updated: 2023/04/25 17:41:04 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_str_matrix_add(char ***matrix, const char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	while (*matrix && (*matrix)[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (*matrix && (*matrix)[i])
	{
		tmp[i] = ft_strdup((*matrix)[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	ft_free_matrix((void ***)matrix);
	*matrix = tmp;
}

size_t	ft_matrix_len(char **matrix)
{
	size_t	i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	return (i);
}

void	ft_matrix_del_last(char **matrix)
{
	size_t	length;

	if (!matrix)
		return ;
	length = ft_matrix_len(matrix);
	if (length == 0)
		return ;
	if (matrix[length - 1])
	{
		free(matrix[length - 1]);
		matrix[length - 1] = NULL;
	}
}

// int	ft_is_string_in_matrix(char *str, char **matrix)
// {
// 	int	i;

// 	i = 0;
// 	while (matrix[i])
// 	{
// 		if (ft_strcmp(matrix[i], str) == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	**ft_matrix_dup(const char **matrix)
// {
// 	char	**dup;
// 	int		i;

// 	i = 0;
// 	while (matrix && matrix[i])
// 		i++;
// 	dup = (char **)malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while (matrix && matrix[i])
// 	{
// 		dup[i] = ft_strdup(matrix[i]);
// 		i++;
// 	}
// 	dup[i] = NULL;
// 	return (dup);
// }

size_t	ft_matrix_size(char **matrix)
{
	size_t	size;
	size_t	i;
	size_t	j;

	size = 0;
	i = 0;
	while (matrix && matrix[i])
	{
		j = 0;
		while (matrix[i][j])
			j++;
		size += j;
		i++;
	}
	return (size);
}

char	*ft_matrix_to_str(char **matrix)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!matrix)
		return (NULL);
	str = (char *)ft_calloc(ft_matrix_size(matrix) + 1, sizeof(char));
	if (!str)
		return (NULL);
	k = 0;
	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			str[k] = matrix[i][j];
			k++;
			j++;
		}
		i++;
	}
	return (str);
}
