/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:58:29 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/23 16:51:04 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_check_access_ret(int acc_ret, char *prefix_msg, char *arg_msg)
{
	if (0 != acc_ret)
	{
		ft_putstr_fd(prefix_msg, 2);
		perror(arg_msg);
		return (0);
	}
	return (1);
}

static int	ft_check_valid_folder(char *path, char *prefix_msg, char *arg_msg)
{
	int		acc_ret;
	char	*trailed_path;
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen_safe(path);
	if (*path == '~')
	{
		ft_putstr_fd(ERROR_CD_HOME, 2);
		return (0);
	}
	if (path[len - 1] != '/')
		trailed_path = ft_strjoin(path, "/");
	else
		trailed_path = ft_strdup(path);
	if (trailed_path)
	{
		acc_ret = access(trailed_path, F_OK);
		free(trailed_path);
		return (ft_check_access_ret(acc_ret, prefix_msg, arg_msg));
	}
	return (0);
}

static void	ft_cd_exe_end(t_built_ins_funct_args *bifa, char *arg, \
							int oldpwd_flag)
{
	char	*new_dir;

	new_dir = NULL;
	if (!bifa->ci->status)
	{
		new_dir = ft_from_relative_to_absolute(arg, bifa->ed->envl);
		if (new_dir)
			bifa->ci->status = !ft_check_valid_folder(new_dir, PERROR_CD, arg);
	}
	if (!bifa->ci->status)
	{
		ft_chdir(bifa, new_dir, arg);
		if (oldpwd_flag)
		{
			if (new_dir)
				ft_putstr_fd(new_dir, 1);
			ft_putstr_fd("\n", 1);
		}
	}
	ft_free((void **)&new_dir);
}

void	ft_cd_exe(t_built_ins_funct_args *bifa)
{
	char	*arg;
	int		oldpwd_flag;

	if (!bifa->ed->envl || !bifa->ci || !bifa->ci->args || \
		!bifa->ci->args[0] || (bifa->ci->args[1] && !*bifa->ci->args[1]))
		return ;
	arg = bifa->ci->args[1];
	if (!arg || !*arg)
		arg = ft_get_envl("HOME", bifa->ed->envl);
	oldpwd_flag = !ft_strcmp(arg, "-");
	bifa->ci->status = 0;
	if (oldpwd_flag)
	{
		arg = ft_get_envl("OLDPWD", bifa->ed->envl);
		if (!arg)
		{
			ft_putstr_fd(ERROR_OLDPWD_NS, 2);
			bifa->ci->status = 1;
		}
	}
	ft_cd_exe_end(bifa, arg, oldpwd_flag);
}
