/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:16:55 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/18 11:58:13 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd_list	*ft_create_cmd_lst(void)
{
	t_cmd_list	*cl;

	cl = malloc (sizeof (t_cmd_list));
	if (cl)
		cl->lst = NULL;
	return (cl);
}

void	ft_fill_cmd_lst(t_cmd_list *cl, char **cmd_line)
{
	char		**cmd;
	int			flag;

	flag = 0;
	cmd = ft_read_command(cmd_line);
	while (cmd && *cmd)
	{
		if (!flag)
			flag = 1;
		else
			*g_status = 0;
		ft_expand_status(cmd);
		ft_append_cmd_to_lst(&cl, ft_init_cmd_info(cmd));
		ft_free_matrix((void ***)&cmd);
		cmd = ft_read_command(cmd_line);
	}
	ft_free_matrix((void ***)&cmd);
}

t_cmd_list	*ft_init_cmd_lst(char **cmd_line)
{
	t_cmd_list	*cl;

	if (!cmd_line)
		return (NULL);
	cl = ft_create_cmd_lst();
	if (cl)
		ft_fill_cmd_lst(cl, cmd_line);
	return (cl);
}

void	ft_dispose_cmd_lst(t_cmd_list **cl)
{
	t_cmd_list	*l;

	if (cl && *cl)
	{
		l = *cl;
		ft_lstclear(&l->lst, ft_dispose_cmd_info);
		ft_free((void **)cl);
	}
}
