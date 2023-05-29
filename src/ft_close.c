/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:44:22 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/24 16:08:51 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_close(int *fd)
{
	int	ret;

	ret = -1;
	if (fd >= 0)
	{
		ret = close(*fd);
		*fd = -1;
	}
	return (ret);
}
