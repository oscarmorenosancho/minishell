/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:40:53 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/16 19:36:41 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_input_redirection(const t_redir_type redir_type)
{
	return (redir_type == redir_inputFile || redir_type == redir_heredoc);
}

int	ft_is_output_redirection(const t_redir_type redir_type)
{
	return (redir_type == redir_outputFile \
			|| redir_type == redir_appendOutputFile);
}

int	ft_is_redirection(char *str)
{
	return (ft_get_redir_type(str));
}

void	ft_append_redir_info(t_cmd_info *cmd_info, t_redir_info *redir_info)
{
	if (cmd_info && redir_info)
	{
		if (ft_is_input_redirection(redir_info->redir_type))
		{
			if (cmd_info->last_input)
				ft_lstadd_back(&cmd_info->redir_list,
					ft_lstnew(cmd_info->last_input));
			cmd_info->last_input = redir_info;
		}
		else if (ft_is_output_redirection(redir_info->redir_type))
		{
			if (cmd_info->last_output)
				ft_lstadd_back(&cmd_info->redir_list,
					ft_lstnew(cmd_info->last_output));
			cmd_info->last_output = redir_info;
		}
	}
}
