/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:59:28 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/26 16:36:26 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env_manage.h"
#include <fcntl.h>

static int	open_n_check(t_built_ins_funct_args *bifa, char *file_name, \
							int flags, int mode)
{
	int		fd;

	fd = -1;
	if (file_name)
	{
		fd = open(file_name, flags, mode);
		if (fd < 0)
		{
			ft_putstr_fd(MSG_DOMOSH, 2);
			perror (file_name);
			bifa->ed->result = 1;
			bifa->ci->status = 1;
		}
	}
	else
	{
		ft_putstr_fd(ERROR_SYN_NL, 2);
		bifa->ed->result = 258;
	}
	return (fd);
}

static void	ft_open_redir_no_filename(t_built_ins_funct_args *bifa, \
										char *tmp_name)
{
	ft_putstr_fd(ERROR_SYN_REDIR, 2);
	if (tmp_name)
		ft_putstr_fd(tmp_name, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	bifa->ed->result = 258;
	bifa->ci->status = 258;
	bifa->abort = 1;
}

int	ft_open_redir(t_built_ins_funct_args *bifa, t_redir_info *ri)
{
	int		fd;
	int		w_perm;
	char	*tmp_name;

	fd = -1;
	if (!ri)
		return (fd);
	tmp_name = ft_remove_quotation_marks(ri->file_name);
	w_perm = S_IWUSR | S_IREAD | S_IRGRP | S_IROTH;
	if (!ri->file_name || ft_is_redirection(ri->file_name))
		ft_open_redir_no_filename(bifa, ri->file_name);
	else if (ri->redir_type == redir_outputFile)
		fd = open_n_check(bifa, tmp_name, O_WRONLY | O_CREAT | O_TRUNC, w_perm);
	else if (ri->redir_type == redir_appendOutputFile)
		fd = open_n_check(bifa, tmp_name, O_WRONLY | O_APPEND | O_CREAT, \
							w_perm);
	else if (ri->redir_type == redir_inputFile)
		fd = open_n_check(bifa, tmp_name, O_RDONLY, 0);
	else if (ri->redir_type == redir_heredoc)
		fd = ft_user_input(bifa, ri->file_name);
	if (fd < 0)
		bifa->abort_redirs = 1;
	free(tmp_name);
	return (fd);
}
