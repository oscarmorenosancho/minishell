/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:53:46 by omoreno-          #+#    #+#             */
/*   Updated: 2022/09/20 17:27:11 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i])
		{
			if (i < dstsize - 1)
				dst[i] = src[i];
			i++;
		}
		if (i < dstsize)
			dst[i] = 0;
		else
			dst[dstsize - 1] = 0;
		return (i);
	}
	else
		return (ft_strlen(src));
}
