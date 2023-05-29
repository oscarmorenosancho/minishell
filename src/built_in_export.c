/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:55:42 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/26 16:30:37 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_export_exe_loop(char *arg, t_exec_data *ed)
{
	char	*eq_pos;
	int		is_append;

	if (!ft_check_valid_env_name(arg))
		return (1);
	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
	{
		ed->envl = ft_set_envl(arg, NULL, &ed->envl);
		return (0);
	}
	is_append = (eq_pos - arg > 2 && *(eq_pos - 1) == '+');
	if (is_append)
		*(eq_pos - 1) = 0;
	*eq_pos = 0;
	if (is_append)
		ft_append_env_value(&ed->envl, arg, eq_pos + 1);
	else
		ed->envl = ft_set_envl(arg, eq_pos + 1, &ed->envl);
	return (0);
}

void	ft_export_exe(t_built_ins_funct_args *bifa)
{
	int	pos;

	if (!bifa->ed->envl)
		return ;
	if (!bifa->ci || !bifa->ci->args \
		|| !bifa->ci->args[0] || !bifa->ci->args[1])
	{
		ft_put_envl(1, bifa->ed->envl, "declare -x ");
		bifa->ci->status = 0;
		return ;
	}
	pos = 1;
	bifa->ci->status = 0;
	while (bifa->ci->args[pos])
		bifa->ci->status |= ft_export_exe_loop(bifa->ci->args[pos++], bifa->ed);
	return ;
}
