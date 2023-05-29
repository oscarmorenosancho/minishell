/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:52:21 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 12:47:52 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_exit_numeric_arg(t_built_ins_funct_args *bifa)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(bifa->ci->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_putchar_fd((unsigned char)255, bifa->fds_status[1]);
}

static void	ft_exit_too_args(t_built_ins_funct_args *bifa)
{
	ft_putstr_fd("exit: too many arguments\n", 2);
	ft_putchar_fd((unsigned char)1, bifa->fds_status[1]);
	ft_close(&bifa->fds_status[1]);
	exit(1);
}

void	ft_exit_exe(t_built_ins_funct_args *bifa)
{
	size_t		len;
	long int	li;

	li = 0;
	if (!bifa->ed->cmd_list->lst->next && isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	len = ft_matrix_len(bifa->ci->args);
	if (len == 1)
		ft_putchar_fd((unsigned char)bifa->ed->result, bifa->fds_status[1]);
	else if (ft_atoli(bifa->ci->args[1], &li))
		ft_exit_numeric_arg(bifa);
	else if (len > 2)
		ft_exit_too_args(bifa);
	else
		ft_putchar_fd((unsigned char)li, bifa->fds_status[1]);
	ft_close(&bifa->fds_status[1]);
	return ;
}
