/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:07:30 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/16 19:48:40 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_fill_cmd_info_init(t_cmd_info *cmd_info, char ***cmd)
{
	if (cmd_info && *cmd)
	{
		while (**cmd && ft_is_redirection(**cmd))
		{
			ft_append_redir_info(cmd_info,
				ft_create_redir_info(*(*cmd + 1), ft_get_redir_type(**cmd)));
			if (*(*cmd + 1))
				(*cmd)++;
			(*cmd)++;
		}
	}
}

void	ft_fill_cmd_info_body(t_cmd_info *cmd_info, char **cmd)
{
	char	*tmp;

	while (cmd && *cmd)
	{
		if (ft_is_redirection(*cmd))
		{
			ft_append_redir_info(cmd_info,
				ft_create_redir_info(*(cmd + 1), ft_get_redir_type(*cmd)));
			cmd++;
		}
		else
		{
			tmp = ft_remove_quotation_marks(*cmd);
			ft_str_matrix_add(&cmd_info->args, tmp);
			free(tmp);
		}
		if (*cmd)
			cmd++;
	}
}
