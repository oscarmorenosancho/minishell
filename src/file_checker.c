/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:48:00 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/19 17:23:14 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_directory(char *filename)
{
	struct stat	sb;

	if (lstat(filename, &sb) == -1)
		return (0);
	return (S_ISDIR(sb.st_mode));
}

int	ft_search_in_env_path(t_built_ins_funct_args *bifa)
{
	char	**paths;
	char	*program[2];
	int		i;

	paths = ft_split_safe(ft_get_envl("PATH", \
							bifa->ed->envl), ':');
	i = 0;
	while (paths && paths[i])
	{
		program[0] = ft_strjoin(paths[i], "/");
		program[1] = ft_strjoin(program[0], bifa->ci->args[0]);
		free(program[0]);
		if (access(program[1], X_OK) == 0 && !ft_is_directory(program[1]))
		{
			ft_free((void **)&bifa->ci->args[0]);
			free(bifa->ci->args[0]);
			bifa->ci->args[0] = program[1];
			ft_free_matrix((void ***)&paths);
			return (0);
		}
		free(program[1]);
		i++;
	}
	ft_free_matrix((void ***)&paths);
	return (127);
}

int	ft_check_if_is_dir(char *filename)
{
	int	is_dir;

	is_dir = ft_is_directory(filename);
	if (is_dir)
	{
		ft_putstr_fd(MSG_DOMOSH, 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(MSG_IS_DIRECTORY, 2);
	}
	return (is_dir);
}

int	ft_search_for_program(t_built_ins_funct_args *bifa)
{
	int		prog_not_found;
	char	*path;

	path = bifa->ci->args[0];
	if (ft_check_if_is_dir(path))
		return (126);
	prog_not_found = access(path, F_OK) != 0;
	if (prog_not_found)
	{
		ft_putstr_fd(MSG_DOMOSH, 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(MSG_COLON, 2);
		perror("");
		return (127);
	}
	prog_not_found = access(path, X_OK) != 0;
	if (prog_not_found)
	{
		prog_not_found = 126;
		ft_putstr_fd(MSG_DOMOSH, 2);
		perror((const char *) path);
	}
	return (prog_not_found);
}

int	ft_search_for_command(t_built_ins_funct_args *bifa)
{
	int		prog_not_found;

	prog_not_found = ft_search_in_env_path(bifa);
	if (prog_not_found)
	{
		ft_putstr_fd(MSG_DOMOSH, 2);
		ft_putstr_fd(bifa->ci->args[0], 2);
		ft_putstr_fd(MSG_COLON, 2);
		ft_putstr_fd(MSG_CMD_NOT_FOUND, 2);
		return (127);
	}
	prog_not_found = access(bifa->ci->args[0], X_OK) != 0;
	if (prog_not_found)
	{
		prog_not_found = 126;
		ft_putstr_fd(MSG_DOMOSH, 2);
		perror((const char *) bifa->ci->args[0]);
	}
	return (prog_not_found);
}
