/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:20:38 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 14:36:07 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env_manage.h"
#include <fcntl.h>

int	ft_open_fdout(t_built_ins_funct_args *bifa, t_cmd_info *ci)
{
	int	fd;

	fd = ft_open_redir(bifa, ci->last_output);
	if (fd < 0)
		fd = open("/dev/null", O_WRONLY, S_IWUSR);
	return (fd);
}

int	ft_open_fdin(t_built_ins_funct_args *bifa, t_cmd_info *ci)
{
	return (ft_open_redir(bifa, ci->last_input));
}

void	ft_open_dummy_redirs(t_built_ins_funct_args *bifa, t_list *redir_lst, \
								int i_o)
{
	int				fd;
	t_redir_type	rt;

	if (redir_lst && !bifa->abort && !bifa->abort_redirs)
	{
		rt = ((t_redir_info *)redir_lst->content)->redir_type;
		if ((!i_o && (rt == redir_inputFile || rt == redir_heredoc)) || \
			(i_o && (rt == redir_outputFile || rt == redir_appendOutputFile)))
		{
			fd = ft_open_redir(bifa, redir_lst->content);
			if (fd >= 0)
				close (fd);
		}
		if (redir_lst->next)
			ft_open_dummy_redirs(bifa, redir_lst->next, i_o);
	}
}

void	ft_prepare_redirs(t_built_ins_funct_args *bifa)
{
	if (bifa->ci->last_input && !bifa->abort && !bifa->abort_redirs)
		bifa->redir_fds[0] = ft_open_fdin(bifa, bifa->ci);
	if (bifa->ci->last_output && !bifa->abort && !bifa->abort_redirs)
		bifa->redir_fds[1] = ft_open_fdout(bifa, bifa->ci);
}
