/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:31:50 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/29 12:52:48 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_error_valid_env_name(char *arg)
{
	ft_putstr_fd(ERROR_NVI_INI, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(ERROR_NVI_END, 2);
}

size_t	ft_varname_len(const char *name)
{
	size_t	len;

	if (! name)
		return (0);
	len = 0;
	while (ft_isalnum(name[len]) || name[len] == '_')
		len++;
	return (len);
}

int	ft_check_valid_env_name(const char *arg)
{
	int	flag;
	int	i;

	flag = 1;
	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		ft_error_valid_env_name((char *)arg);
		return (0);
	}
	while (arg[i] && arg[i] != '=' && flag)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			flag = 0;
		else
			i++;
	}
	if (arg[i] == '+' && arg[i + 1] == '=')
		flag = 1;
	if (!flag)
		ft_error_valid_env_name((char *)arg);
	return (flag);
}
