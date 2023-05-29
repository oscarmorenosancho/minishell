/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:31:49 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/19 15:50:34 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*ft_search_env(t_list *lst, char *name)
{
	t_list	*cur;
	char	*cur_name;

	if (!lst)
		return (NULL);
	cur = lst;
	if (cur->content)
		cur_name = ((t_env_var *)cur->content)->name;
	while (cur && ft_strcmp(cur_name, name))
	{
		cur = cur->next;
		if (cur && cur->content)
			cur_name = ((t_env_var *)cur->content)->name;
	}
	return (cur);
}

t_list	*ft_lstextract(t_list **lst, t_list *node)
{
	t_list	*cur;

	if (!lst || !*lst || !node)
		return (NULL);
	cur = *lst;
	if (cur == node)
	{
		*lst = cur->next;
		return (*lst);
	}
	while (cur && cur->next != node)
		cur = cur->next;
	if (cur)
		cur->next = node->next;
	node->next = NULL;
	return (*lst);
}

void	ft_update_env_value(t_list *node, char *value)
{
	if (node && value)
	{
		ft_free((void **)&((t_env_var *)node->content)->value);
		((t_env_var *)node->content)->value = ft_strdup(value);
	}
}

void	ft_set_env_value(t_list **lst, char *name, char *value)
{
	t_list	*node;

	node = ft_search_env(*lst, name);
	if (node)
		ft_update_env_value(node, value);
	else
		ft_append_env_node(lst, name, value);
}

void	ft_append_env_value(t_list **lst, char *name, char *con_value)
{
	t_list	*node;
	char	*aux_value;

	if (!con_value)
		return ;
	aux_value = NULL;
	node = ft_search_env(*lst, name);
	if (node)
	{
		aux_value = ((t_env_var *)node->content)->value;
		if (aux_value)
			((t_env_var *)node->content)->value = \
						ft_strjoin(aux_value, con_value);
		ft_free((void **)&aux_value);
	}
	else
		ft_append_env_node(lst, name, con_value);
}
