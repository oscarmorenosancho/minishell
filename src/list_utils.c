/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:40:14 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/24 16:11:54 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

t_list	*ft_lstreverse(t_list **lst)
{
	t_list	*next;
	t_list	*rev_list;

	if (! lst || ! *lst)
		return (NULL);
	rev_list = NULL;
	while (*lst)
	{
		next = (*lst)->next;
		(*lst)->next = NULL;
		ft_lstadd_front(&rev_list, *lst);
		*lst = next;
	}
	return (rev_list);
}

t_list	*ft_lstduprev_n_size(t_list *lst, size_t *len)
{
	t_list	*rev_list;
	t_list	*node;
	t_list	*cur;
	size_t	i;

	if (! lst)
		return (NULL);
	cur = lst;
	rev_list = NULL;
	i = 0;
	while (cur)
	{
		node = ft_lstnew(cur->content);
		if (node)
			ft_lstadd_front(&rev_list, node);
		i++;
		cur = cur->next;
	}
	if (len)
		*len = i;
	return (rev_list);
}

void	ft_lstreduce(t_list *lst, t_reduce_funct f, void *arg)
{
	t_list			*cur;
	unsigned int	i;

	cur = lst;
	i = 0;
	if (f && arg)
	{
		while (cur)
		{	
			(*f)(i, (void *)cur->content, arg);
			cur = cur->next;
			i++;
		}
	}
}

t_list	*ft_lstsort(t_list **lst, int (*comp)(void *, void *))
{
	t_list	*next;
	t_list	*sorted_list;
	t_list	*ins_pos;

	if (! lst || ! *lst)
		return (NULL);
	sorted_list = NULL;
	while (*lst)
	{
		next = (*lst)->next;
		(*lst)->next = NULL;
		ins_pos = ft_search_env_inspos(sorted_list, *lst, comp);
		if (ins_pos)
			ft_lstadd_front(&ins_pos->next, *lst);
		else
			ft_lstadd_front(&sorted_list, *lst);
		*lst = next;
	}
	return (sorted_list);
}
