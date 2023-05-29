/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:54:09 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/19 17:21:02 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env_exe(t_built_ins_funct_args *bifa)
{
	if (bifa->ed->envl)
		ft_put_envl(1, bifa->ed->envl, NULL);
	bifa->ci->status = 0;
	return ;
}
