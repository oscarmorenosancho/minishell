/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:54:36 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/29 09:25:37 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_update_pwd(char *new_dir, \
				char *oldpwd, t_built_ins_funct_args *bifa)
{
	int		len;
	char	*priv;
	int		priv_len;

	len = ft_strlen_safe(new_dir);
	if (new_dir[len - 1] == '/')
		new_dir[len - 1] = 0;
	else if (new_dir[len - 1] == '.' && new_dir[len - 2] == '/')
		new_dir[len - 2] = 0;
	priv = "/private";
	priv_len = ft_strlen(priv);
	if (ft_strncmp(new_dir, priv, priv_len) == 0)
		new_dir += priv_len;
	if (*new_dir)
		bifa->ed->envl = ft_set_envl("PWD", new_dir, &bifa->ed->envl);
	else
		bifa->ed->envl = ft_set_envl("PWD", "/", &bifa->ed->envl);
	bifa->ed->envl = ft_set_envl("OLDPWD", oldpwd, &bifa->ed->envl);
	bifa->ed->result = 0;
}

void	ft_chdir(t_built_ins_funct_args *bifa, char *new_dir, char *arg)
{
	char	buf[500];
	char	*oldpwd;
	char	*priv;
	int		priv_len;

	priv = "/private";
	priv_len = ft_strlen(priv);
	oldpwd = getcwd(buf, 500);
	if (!oldpwd)
	{
		ft_putstr_fd(ERROR_GETCWD, 2);
		return ;
	}
	if (ft_strncmp(oldpwd, priv, priv_len) == 0)
		oldpwd += priv_len;
	if (new_dir && chdir(new_dir) != 0)
	{
		ft_putstr_fd(PERROR_CD, 2);
		perror(arg);
		bifa->ci->status = 1;
	}
	else if (new_dir && *oldpwd)
		ft_update_pwd(new_dir, oldpwd, bifa);
	else if (new_dir)
		ft_update_pwd(new_dir, "/", bifa);
}
