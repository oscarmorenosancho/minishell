/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:02:23 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 14:43:35 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cmd_builtins(t_built_ins_funct_args *bifa)
{
	pid_t	fork_ret;

	ft_prepare_redirs(bifa);
	if (!bifa->ed->cmd_list->lst->next && !bifa->abort_redirs)
	{
		ft_redir_pipe_ini_on_child(bifa, 0);
		if (get_built_in(bifa->ci->cmd_id) && !bifa->abort)
			get_built_in(bifa->ci->cmd_id)(bifa);
		return ;
	}
	if (bifa->abort || bifa->abort_redirs)
		return ;
	ft_create_pipe(bifa);
	ft_handler_ignore();
	fork_ret = fork();
	if (fork_ret == 0)
	{
		ft_handlers_son();
		ft_redir_pipe_ini_on_child(bifa, 1);
		get_built_in(bifa->ci->cmd_id)(bifa);
		exit(0);
	}
	ft_redir_pipe_end_on_parent(bifa, 1);
	bifa->ci->pid = fork_ret;
}

static int	ft_get_prog_not_found(t_built_ins_funct_args *bifa)
{
	if (!ft_get_envl("PATH", bifa->ed->envl) || bifa->ci->cmd_id == cmd_exec)
		return (ft_search_for_program(bifa));
	return (ft_search_for_command(bifa));
}

static void	ft_cmd_others_son(t_built_ins_funct_args *bifa)
{
	int		prog_not_found;
	char	**aux_env;

	ft_handlers_son();
	ft_redir_pipe_ini_on_child(bifa, 1);
	prog_not_found = ft_get_prog_not_found(bifa);
	if (! prog_not_found)
	{
		aux_env = ft_env_var_2_matrix(bifa->ed->envl);
		execve(bifa->ci->args[0], bifa->ci->args, aux_env);
		ft_free_matrix((void ***)&aux_env);
	}
	exit(prog_not_found);
}

void	ft_cmd_others(t_built_ins_funct_args *bifa)
{
	pid_t	fork_ret;

	ft_create_pipe(bifa);
	ft_prepare_redirs(bifa);
	if (bifa->abort || bifa->abort_redirs)
	{
		ft_redir_pipe_end_on_parent(bifa, 0);
		ft_close(&bifa->pipe_fds[1]);
		return ;
	}
	ft_handler_ignore();
	fork_ret = fork();
	if (fork_ret == 0)
		ft_cmd_others_son(bifa);
	ft_redir_pipe_end_on_parent(bifa, 1);
	bifa->ci->pid = fork_ret;
	if (fork_ret > 0 && bifa->i == 0)
		kill(fork_ret, SIGSTOP);
}

void	ft_cmd_info_exe(t_built_ins_funct_args *bifa)
{
	bifa->abort_redirs = 0;
	ft_open_dummy_redirs(bifa, bifa->ci->redir_list, 0);
	if (bifa->abort || bifa->abort_redirs)
		return ;
	if (bifa->ci->cmd_id == cmd_exec || bifa->ci->cmd_id == cmd_unknown)
		ft_cmd_others(bifa);
	else if (bifa->ci->cmd_id == cmd_exit)
		ft_cmd_exit(bifa);
	else if (bifa->ci->cmd_id >= 0 && bifa->ci->cmd_id < cmd_exit)
		ft_cmd_builtins(bifa);
	if (bifa->abort || bifa->abort_redirs)
		return ;
	ft_open_dummy_redirs(bifa, bifa->ci->redir_list, 1);
}
