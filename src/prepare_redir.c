/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:23:06 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 17:17:11 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_create_pipe(t_built_ins_funct_args *bifa)
{
	if (!bifa->last)
		pipe(bifa->pipe_fds);
	else
	{
		bifa->pipe_fds[0] = bifa->tmp_stfds[0];
		bifa->pipe_fds[1] = bifa->tmp_stfds[1];
	}
}

void	ft_redir_pipe_ini_on_child(t_built_ins_funct_args *bifa, int flag_fork)
{
	if (flag_fork)
		ft_close(&bifa->pipe_fds[0]);
	ft_dup2(&bifa->pipe_fds[1], STDOUT_FILENO);
	ft_dup2(&bifa->redir_fds[0], STDIN_FILENO);
	ft_dup2(&bifa->redir_fds[1], STDOUT_FILENO);
}

void	ft_redir_pipe_end_on_parent(t_built_ins_funct_args *bifa, int flag_fork)
{
	if (flag_fork)
	{
		ft_close(&bifa->pipe_fds[1]);
		ft_close(&bifa->redir_fds[0]);
		ft_close(&bifa->redir_fds[1]);
	}
	ft_dup2(&bifa->pipe_fds[0], STDIN_FILENO);
}
