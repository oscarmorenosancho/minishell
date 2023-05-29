/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_safe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:57:41 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/18 17:06:01 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_split_safe(char const *s, char c)
{
	if (!s)
		return (NULL);
	if (!*s)
		return (ft_calloc(1, sizeof(char **)));
	return (ft_split(s, c));
}
