/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:54:21 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/24 16:11:38 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_dup2(int *fd_src, int fd_dest)
{
	int	ret;

	ret = -1;
	if (*fd_src >= 0 && fd_dest >= 0)
		ret = dup2(*fd_src, fd_dest);
	ft_close(fd_src);
	return (ret);
}
