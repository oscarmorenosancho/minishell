/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:16:44 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 13:09:45 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_exit_father(t_built_ins_funct_args *bifa, pid_t fork_ret)
{
	int				status;
	int				read_status;
	unsigned char	buff;

	buff = '\0';
	ft_close(&bifa->fds_status[1]);
	ft_redir_pipe_end_on_parent(bifa, 1);
	waitpid(fork_ret, &status, 0);
	read_status = read(bifa->fds_status[0], &buff, 1);
	ft_close(&bifa->fds_status[0]);
	if (read_status >= 0)
		bifa->ci->status = buff;
	else
		bifa->ci->status = read_status;
	if (!WEXITSTATUS(status) && !bifa->ed->cmd_list->lst->next)
		exit(bifa->ci->status);
}

static void	ft_exit_son(t_built_ins_funct_args *bifa)
{
	ft_handlers_son();
	ft_close(&bifa->fds_status[0]);
	ft_redir_pipe_ini_on_child(bifa, 1);
	if (get_built_in(bifa->ci->cmd_id))
		get_built_in(bifa->ci->cmd_id)(bifa);
	exit(0);
}

void	ft_cmd_exit(t_built_ins_funct_args *bifa)
{
	pid_t	fork_ret;

	ft_prepare_redirs(bifa);
	if (bifa->abort || bifa->abort_redirs)
	{
		ft_close(&bifa->pipe_fds[1]);
		return ;
	}
	pipe(bifa->fds_status);
	ft_create_pipe(bifa);
	ft_handler_ignore();
	fork_ret = fork();
	if (fork_ret == 0)
		ft_exit_son(bifa);
	else
		ft_exit_father(bifa, fork_ret);
}
