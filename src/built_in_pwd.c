/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:20:37 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/23 16:54:42 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd_exe(t_built_ins_funct_args *bifa)
{
	char	buf[500];
	char	*ret;
	char	*priv;
	int		priv_len;

	if (!bifa->ed->envl)
		return ;
	priv = "/private";
	priv_len = ft_strlen(priv);
	ret = getcwd(buf, 500);
	if (!ret)
		ret = ft_get_envl("PWD", bifa->ed->envl);
	if (ret)
	{
		if (ft_strncmp(ret, priv, priv_len) == 0)
			ret += priv_len;
		if (*ret)
			write(1, ret, ft_strlen_safe(ret));
		else
			write(1, "/", 1);
		write(1, "\n", 1);
	}
	else
		ft_putstr_fd(ERROR_PWD_NS, 2);
	bifa->ci->status = 0;
}
