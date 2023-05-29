/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:25:55 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/08 17:26:08 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_append_cmd_to_lst(t_cmd_list **cl, t_cmd_info *ci)
{
	t_list	*node;

	if (cl && ci)
	{
		node = ft_lstnew(ci);
		if (node)
			ft_lstadd_back(&(*cl)->lst, node);
	}
	return (0);
}

t_cmd_info	*ft_get_cmd_from_lst(t_cmd_list **cl, int index)
{
	t_list		*ci;
	t_list		*cur;
	int			i;

	ci = NULL;
	if (cl && *cl)
	{
		i = 0;
		cur = (*cl)->lst;
		while (cur && i < index)
		{
			cur = cur->next;
			i++;
		}
		if (i == index)
			ci = cur;
	}
	return (ci->content);
}
