/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:31:49 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/19 19:33:15 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_var	*ft_create_env_var(char *name, char *value)
{
	t_env_var	*env_var;

	if (!name)
		return (NULL);
	env_var = (t_env_var *) malloc(sizeof(t_env_var));
	if (env_var)
	{
		env_var->name = ft_strdup(name);
		env_var->value = NULL;
		if (value)
			env_var->value = ft_strdup(value);
	}
	return (env_var);
}

void	ft_dispose_env_var(void *env_var)
{
	if (env_var)
	{
		ft_free((void **)&((t_env_var *)env_var)->name);
		ft_free((void **)&((t_env_var *)env_var)->value);
		free(env_var);
	}
}

t_list	*ft_create_env_node(char *name, char *value)
{
	t_env_var	*env_var;

	env_var = ft_create_env_var(name, value);
	if (env_var)
		return (ft_lstnew((void *)env_var));
	return (NULL);
}

void	ft_append_env_node(t_list **lst, char *name, char *value)
{
	t_list	*node;

	if (!lst)
		return ;
	node = ft_create_env_node(name, value);
	if (node)
		ft_lstadd_front(lst, node);
}
