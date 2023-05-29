/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:25:51 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/16 19:36:11 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redir_info	*ft_create_redir_info(char *file_name, t_redir_type redir_type)
{
	t_redir_info	*ri;

	ri = (t_redir_info *)malloc(sizeof(t_redir_info));
	if (ri)
	{
		ri->file_name = NULL;
		if (file_name)
			ri->file_name = ft_strdup(file_name);
		ri->redir_type = redir_type;
	}
	return (ri);
}

void	ft_dispose_redir_info(void *ri)
{
	t_redir_info	*rip;

	if (ri)
	{
		rip = ri;
		ft_free((void **)&(rip->file_name));
		free(ri);
	}
}

t_redir_type	ft_get_redir_type(char *redir_type)
{
	if (!redir_type || !*redir_type)
		return (redir_none);
	if (ft_strcmp(redir_type, "<") == 0)
		return (redir_inputFile);
	if (ft_strcmp(redir_type, "<<") == 0)
		return (redir_heredoc);
	if (ft_strcmp(redir_type, ">") == 0)
		return (redir_outputFile);
	if (ft_strcmp(redir_type, ">>") == 0)
		return (redir_appendOutputFile);
	return (redir_none);
}
