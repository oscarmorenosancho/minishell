/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:11:31 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 13:23:39 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_init_bifa(t_built_ins_funct_args	*bifa, t_exec_data *ed)
{
	bifa->ed = ed;
	bifa->tmp_stfds[0] = dup(STDIN_FILENO);
	bifa->tmp_stfds[1] = dup(STDOUT_FILENO);
	bifa->pipe_fds[0] = -1;
	bifa->pipe_fds[1] = -1;
	bifa->redir_fds[0] = -1;
	bifa->redir_fds[1] = -1;
	bifa->abort = 0;
	bifa->abort_redirs = 0;
}

void	ft_cmd_iter(t_exec_data *ed)
{
	t_list					*cur;
	int						i;
	t_built_ins_funct_args	bifa;

	cur = ed->cmd_list->lst;
	i = 0;
	ft_init_bifa(&bifa, ed);
	while (cur)
	{
		bifa.ci = cur->content;
		bifa.i = i;
		bifa.last = (cur->next == NULL);
		ft_cmd_info_exe(&bifa);
		cur = cur->next;
		i++;
	}
	ft_wait_for_pids(&bifa);
	ft_dups2(bifa.tmp_stfds);
}

int	ft_cmd_exe(t_exec_data *ed)
{
	if (!ed->cmd_list || !ed->envl)
		return (0);
	ft_cmd_iter(ed);
	return (0);
}
