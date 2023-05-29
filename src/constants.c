/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:02:17 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/09 16:48:13 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_built_in_funct	get_built_in(t_cmd_id id)
{
	static const t_built_in_funct	g_built_in_ar[] = {\
		ft_none_exe, \
		ft_echo_exe, \
		ft_cd_exe, ft_pwd_exe, \
		ft_export_exe, ft_unset_exe, ft_env_exe, \
		ft_exit_exe, NULL, NULL};

	return (g_built_in_ar[id]);
}
