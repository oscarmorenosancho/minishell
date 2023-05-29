/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:33:48 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/22 12:48:24 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*ft_envl_init(char **original)
{
	t_list	*l;

	l = NULL;
	if (!original)
		return (l);
	l = ft_env_var_2_list(original);
	if (l)
	{
		ft_increase_shlvl_envl(&l);
		ft_unset_envl("OLDPWD", &l);
	}
	return (l);
}

char	*ft_get_envl(const char *str, t_list *envl)
{
	t_list		*node;
	t_env_var	*ev;
	char		*name;
	int			name_len;

	name_len = ft_varname_len(str);
	if (name_len > 0)
	{
		name = ft_substr(str, 0, name_len);
		node = ft_search_env(envl, (char *)name);
		free(name);
		if (node)
		{
			ev = (t_env_var *)node->content;
			return (ev->value);
		}
	}
	return (NULL);
}

t_list	*ft_set_envl(const char *name, const char *src, t_list **envl)
{
	ft_set_env_value(envl, (char *)name, (char *)src);
	return (*envl);
}

t_list	*ft_unset_envl(const char *name, t_list **envl)
{
	t_list	*node;
	t_list	*l;

	l = NULL;
	node = ft_search_env(*envl, (char *)name);
	if (node)
	{
		l = ft_lstextract(envl, node);
		ft_lstdelone(node, ft_dispose_env_var);
	}
	return (l);
}

void	ft_put_envl(int fd, t_list *envl, char *prefix)
{
	if (!envl)
		return ;
	if (prefix && *prefix)
		ft_lstreduce(envl, ft_print_exp_var_line, (void *)(long int)fd);
	else
		ft_lstreduce(envl, ft_print_env_var_line, (void *)(long int)fd);
}
