/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:28:20 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/22 17:01:37 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_get_home(t_list *envl)
{
	char	*home;
	char	*user;

	home = ft_get_envl("HOME", envl);
	if (!home)
	{
		user = ft_get_envl("USER", envl);
		if (!user)
			return (ft_strdup("/Users"));
		if (*user == '/')
			return (ft_strjoin("/Users", user));
		return (ft_strjoin("/Users/", user));
	}
	return (ft_strdup(home));
}

static void	ft_add_home(char **initialized_relative_path, char **relative_path, \
						t_list *envl)
{
	char	*tmp;

	tmp = ft_get_home(envl);
	ft_stradd_str(initialized_relative_path, tmp);
	free(tmp);
	*relative_path += 2;
}

char	*ft_init_path(char *relative_path, t_list *envl)
{
	char	*initialized_relative_path;
	char	buf[500];
	char	*cwd;

	cwd = getcwd(buf, 500);
	if (!cwd)
		cwd = ft_get_envl("PWD", envl);
	initialized_relative_path = NULL;
	if (!relative_path)
		return (ft_strdup("~"));
	if (ft_strncmp(relative_path, "~/", 2) == 0 || \
			ft_strcmp(relative_path, "~") == 0)
		ft_add_home(&initialized_relative_path, &relative_path, envl);
	else if (ft_strncmp(relative_path, "../", 3) == 0)
		ft_stradd_str(&initialized_relative_path, cwd);
	else if (relative_path[0] && relative_path[0] != '/')
		ft_stradd_str(&initialized_relative_path, cwd);
	if (initialized_relative_path && \
			ft_get_last_char(initialized_relative_path) != '/')
		ft_stradd_char(&initialized_relative_path, '/');
	ft_stradd_str(&initialized_relative_path, relative_path);
	return (initialized_relative_path);
}
