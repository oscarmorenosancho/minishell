/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:59:16 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 12:31:33 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_continue_pids(t_built_ins_funct_args *bifa)
{
	t_list		*cl;
	t_cmd_info	*ci;

	cl = bifa->ed->cmd_list->lst;
	while (cl)
	{
		ci = (t_cmd_info *)cl->content;
		if (ci->pid > 0)
			kill(ci->pid, SIGCONT);
		cl = cl->next;
	}
}

void	ft_putstr_repl_line_n_redisp(char *str_2_put, char *str_2_repl)
{
	ft_putstr_fd(str_2_put, 1);
	rl_replace_line(str_2_repl, 0);
	rl_redisplay();
}

pid_t	ft_wait_for_status(t_built_ins_funct_args *bifa, t_cmd_info *ci)
{
	pid_t	wait_ret;
	int		status;

	wait_ret = waitpid(ci->pid, &status, 0);
	if (bifa->abort)
		ft_putstr_repl_line_n_redisp("\n", "");
	else if (WIFSIGNALED(status) && WTERMSIG(status) != SIGPIPE)
	{
		bifa->abort = 1;
		ci->status = WTERMSIG(status) + 128;
		if (ci->status == SIGINT + 128)
			ft_putstr_repl_line_n_redisp("\n", "");
		else if (ci->status == SIGQUIT + 128)
			ft_putstr_repl_line_n_redisp("Quit: 3\n", "");
	}
	else
		ci->status = WEXITSTATUS(status);
	return (wait_ret);
}

void	ft_wait_for_pids(t_built_ins_funct_args *bifa)
{
	t_list		*cl;
	t_cmd_info	*ci;

	ft_continue_pids(bifa);
	cl = bifa->ed->cmd_list->lst;
	while (cl && !bifa->abort)
	{
		ci = (t_cmd_info *)cl->content;
		if (ci->pid > 0)
		{
			if (ft_wait_for_status(bifa, ci) == -1)
			{
				ci->status = 1;
				perror (MSG_DOMOSH);
			}
		}
		bifa->ed->result = ci->status;
		cl = cl->next;
	}
}
