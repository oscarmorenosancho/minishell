/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:27:57 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/23 16:50:15 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_from_relative_to_absolute(char *relative_path, t_list *envl)
{
	char	*relative_path_formated;
	char	*absolute_path;
	char	**splited_path;
	char	*dir;

	relative_path_formated = ft_init_path(relative_path, envl);
	splited_path = NULL;
	dir = ft_read_dir(relative_path_formated);
	while (relative_path_formated && dir)
	{
		ft_append_dir(&splited_path, dir);
		dir = ft_read_dir(relative_path_formated);
	}
	ft_free((void **)&relative_path_formated);
	absolute_path = ft_matrix_to_str(splited_path);
	ft_free_matrix((void ***)&splited_path);
	return (absolute_path);
}

void	ft_append_dir(char ***splited_path, char *dir)
{
	if (!dir || !*dir || !splited_path)
		return ;
	if (*splited_path && **splited_path && *(*splited_path + 1)
		&& (ft_strcmp(dir, "../") == 0 || ft_strcmp(dir, "..") == 0))
		ft_matrix_del_last(*splited_path);
	else if (ft_strcmp(dir, "./") != 0 && ft_strcmp(dir, "..") != 0)
		ft_str_matrix_add(splited_path, dir);
	free(dir);
}

char	*ft_read_dir(char *path)
{
	static char	*ref = NULL;
	static int	pos = 0;
	char		*dir;

	if (!path || !path[pos])
	{
		pos = 0;
		return (NULL);
	}
	if (ref != path)
	{
		pos = 0;
		ref = path;
	}
	dir = NULL;
	ft_stradd_char(&dir, path[pos]);
	while (path[pos] && path[pos] != '/')
	{
		pos++;
		ft_stradd_char(&dir, path[pos]);
	}
	if (path[pos])
		pos++;
	return (dir);
}
