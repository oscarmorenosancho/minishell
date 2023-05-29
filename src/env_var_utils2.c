/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:24 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/19 13:27:15 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_env_var_2_matrix(t_list *l)
{
	char	**ret;
	size_t	var_count;
	t_list	*duprev_l;

	if (!l)
		return (NULL);
	var_count = 0;
	duprev_l = ft_lstduprev_n_size(l, &var_count);
	ret = malloc(sizeof(char *) * (var_count + 1));
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, sizeof(char *) * (var_count + 1));
	ft_lstreduce(duprev_l, &ft_format_env_var_line, (void *)ret);
	ft_lstclear(&duprev_l, NULL);
	return (ret);
}

t_list	*ft_env_line_2_node(char *line)
{
	char		**matrix;
	char		*exist_eq;
	t_list		*node;
	t_env_var	*content;

	matrix = ft_split_safe(line, '=');
	if (!matrix || !matrix[0])
		return (NULL);
	exist_eq = ft_strchr(line, '=');
	if (exist_eq && !matrix[1])
		content = ft_create_env_var(matrix[0], "");
	else
		content = ft_create_env_var(matrix[0], matrix[1]);
	ft_free_matrix((void ***)&matrix);
	node = ft_lstnew(content);
	if (!node)
		ft_dispose_env_var(content);
	return (node);
}

t_list	*ft_env_var_2_list(char **t)
{
	t_list		*ret;
	t_list		*node;
	char		**tab;

	if (!t)
		return (NULL);
	tab = t;
	ret = NULL;
	while (*tab)
	{
		node = ft_env_line_2_node(*tab);
		if (node)
			ft_lstadd_front(&ret, node);
		tab++;
	}
	return (ft_lstreverse(&ret));
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*l;
// 	// char	**m;
// 	// char	**r;

// 	(void)argc;
// 	(void)argv;
// 	l = ft_envl_init(envp);
// 	// l = ft_env_var_2_list(envp);
// 	//ft_lstreduce(l, ft_print_env_var_line, (void *)2);
// 	//ft_lstreduce(l, ft_print_exp_var_line, (void *)2);
// 	//  m = ft_env_var_2_matrix(l);
// 	// r = m;
// 	// while (*r)
// 	// {
// 	// 	ft_putstr_fd(*r, 2);
// 	// 	ft_putstr_fd("\n", 2);
// 	// 	r++;
// 	// }
// 	// ft_free_matrix((void ***)&m);
// 	// ft_unset_envl("USER", &l);
// 	// ft_unset_envl("_", &l);
// 	// ft_unset_envl("LANG", &l);
// 	// ft_unset_envl("SHLVL", &l);
// 	// ft_increase_shlvl_envl(&l);
// 	// ft_increase_shlvl_envl(&l);
// 	// ft_unset_envl("OLDPWD", &l);
// 	// ft_append_env_value(&l, "SHLVL", "hola");
// 	ft_put_envl(1, l, 0);
// 	ft_lstclear(&l, ft_dispose_env_var);
// 	return (0);
// }
