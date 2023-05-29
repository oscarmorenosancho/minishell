/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:43:53 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/10 15:41:03 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

// void	ft_free(char **str)
// {
// 	if (*str)
// 	{
// 		free(*str);
// 		*str = NULL;
// 	}
// }

// void	ft_free_matrix(char ***matrix)
// {
// 	int	i;

// 	i = 0;
// 	while (*matrix && (*matrix)[i])
// 	{
// 		if ((*matrix)[i])
// 		{
// 			free((*matrix)[i]);
// 			(*matrix)[i] = NULL;
// 		}
// 		i++;
// 	}
// 	if (*matrix)
// 	{
// 		free(*matrix);
// 		*matrix = NULL;
// 	}
// }

void	ft_free(void **mem)
{
	if (mem && *mem)
	{
		free(*mem);
		*mem = NULL;
	}
}

void	ft_free_matrix(void ***matrix)
{
	int	i;

	i = 0;
	while (matrix && *matrix && (*matrix)[i])
	{
		ft_free((void **)&(*matrix)[i]);
		i++;
	}
	ft_free((void **)matrix);
}
