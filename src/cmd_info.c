/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:33:20 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/22 17:41:15 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// t_cmd_info	*ft_create_cmd_info(t_cmd_id cid)
t_cmd_info	*ft_create_cmd_info(void)
{
	t_cmd_info	*ci;

	ci = malloc(sizeof(t_cmd_info));
	if (ci)
	{
		ci->cmd_id = cmd_none;
		ci->pid = 0;
		ci->status = 0;
		ci->args = NULL;
		ci->redir_list = NULL;
		ci->last_input = NULL;
		ci->last_output = NULL;
	}
	return (ci);
}

void	ft_dispose_cmd_info(void *ci)
{
	if (ci)
	{
		ft_free_matrix((void ***)&((t_cmd_info *)ci)->args);
		if (((t_cmd_info *)ci)->redir_list)
			ft_lstclear(&((t_cmd_info *)ci)->redir_list, ft_dispose_redir_info);
		if (((t_cmd_info *)ci)->last_input)
			ft_dispose_redir_info((void *)((t_cmd_info *)ci)->last_input);
		if (((t_cmd_info *)ci)->last_output)
			ft_dispose_redir_info((void *)((t_cmd_info *)ci)->last_output);
		free(ci);
	}
}

t_cmd_id	ft_get_cmd_id(char *cmd_name)
{
	if (!cmd_name || !*cmd_name)
		return (cmd_none);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (cmd_echo);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (cmd_cd);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (cmd_pwd);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (cmd_export);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (cmd_unset);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (cmd_env);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (cmd_exit);
	if (ft_is_path(cmd_name))
		return (cmd_exec);
	return (cmd_unknown);
}

// the parameter cmd is only 1 command
// int	ft_init_cmd_info(t_cmd_info *cmd_info, const char **cmd)
t_cmd_info	*ft_init_cmd_info(char **cmd)
{
	t_cmd_info	*cmd_info;

	cmd_info = ft_create_cmd_info();
	if (cmd_info && cmd)
	{
		ft_fill_cmd_info(cmd_info, cmd);
		return (cmd_info);
	}
	return (NULL);
}

void	ft_fill_cmd_info(t_cmd_info *cmd_info, char **cmd)
{
	char	*cmd_no_qm;

	if (cmd_info && cmd)
	{
		ft_fill_cmd_info_init(cmd_info, &cmd);
		cmd_no_qm = ft_remove_quotation_marks(*cmd);
		cmd_info->cmd_id = ft_get_cmd_id(cmd_no_qm);
		free(cmd_no_qm);
		ft_fill_cmd_info_body(cmd_info, cmd);
	}
}
