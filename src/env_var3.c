/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:25:17 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 16:01:17 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env_comp(void *arg1, void *arg2)
{
	t_env_var	*ev1;
	t_env_var	*ev2;

	if (arg1 == arg2)
		return (0);
	if (!arg1 && arg2)
		return (1);
	if (arg1 && !arg2)
		return (-1);
	ev1 = arg1;
	ev2 = arg2;
	return (ft_strcmp(ev2->name, ev1->name));
}

t_list	*ft_search_env_inspos(t_list *lst, t_list *to_ins, \
								int (*comp)(void *, void *))
{
	t_list	*cur;

	if (!lst || !to_ins)
		return (NULL);
	cur = lst;
	if (comp(cur->content, to_ins->content) < 0)
		return (NULL);
	while (cur && cur->next && \
			comp(cur->next->content, to_ins->content) > 0)
		cur = cur->next;
	return (cur);
}
