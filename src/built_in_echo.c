/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:00:03 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/15 17:04:13 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_check_not_flag(char *s, int *print_ret)
{
	int	i;

	if (s[0] != '-')
		return (1);
	i = 1;
	while (s[i] == 'n')
		i++;
	if (i > 1 && s[i] == 0)
	{
		*print_ret = 0;
		return (0);
	}
	return (1);
}

static void	ft_echo_arg(t_built_ins_funct_args *bifa, int i)
{
	ft_putstr_fd(bifa->ci->args[i], 1);
	if (bifa->ci->args[i + 1])
		ft_putchar_fd(' ', 1);
}

static int	ft_echo_args(t_built_ins_funct_args *bifa)
{
	int	i;
	int	found_not_flag;
	int	print_ret;

	found_not_flag = 0;
	i = 0;
	print_ret = 1;
	while (bifa->ci->args[i])
	{
		if (i > 0)
		{
			if (! found_not_flag)
				found_not_flag = \
					ft_check_not_flag(bifa->ci->args[i], &print_ret);
			if (found_not_flag)
				ft_echo_arg(bifa, i);
		}
		i++;
	}
	return (print_ret);
}

void	ft_echo_exe(t_built_ins_funct_args *bifa)
{
	if (bifa && ft_echo_args(bifa))
		ft_putchar_fd('\n', 1);
	bifa->ci->status = 0;
}
