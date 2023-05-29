/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:55:07 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/23 17:00:23 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset_exe(t_built_ins_funct_args *bifa)
{
	int	i;

	if (!bifa->ci || !bifa->ci->args \
		|| !bifa->ci->args[1] || !bifa->ed->envl)
		return ;
	i = 1;
	while (bifa->ci->args[i])
	{
		ft_unset_envl(bifa->ci->args[i], &bifa->ed->envl);
		i++;
	}
	bifa->ci->status = 0;
	return ;
}
