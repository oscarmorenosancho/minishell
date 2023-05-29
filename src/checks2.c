/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:51:08 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/26 17:45:30 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_syntax_error(char *name)
{
	ft_putstr_fd(ERROR_SYN_REDIR, 2);
	if (name)
		ft_putstr_fd(name, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

static int	ft_check_redirs_loop(int flag_redir, char *str)
{
	if (!str || ft_is_redirection(str) || !ft_strcmp(str, "|"))
	{
		if (flag_redir)
		{
			ft_syntax_error(str);
			return (1);
		}
	}
	return (0);
}

int	ft_check_redirs(char **matrix)
{
	int		i;
	int		flag_redir;

	if (!matrix)
		return (0);
	flag_redir = 0;
	i = 0;
	while (matrix[i])
	{
		if (ft_check_redirs_loop(flag_redir, matrix[i]))
			return (1);
		if (ft_is_redirection(matrix[i]))
			flag_redir = 1;
		else if (matrix[i])
			flag_redir = 0;
		i++;
	}
	if (flag_redir)
	{
		ft_putstr_fd(ERROR_SYN_REDIR, 2);
		ft_putstr_fd("newline", 2);
		ft_putstr_fd("'\n", 2);
	}
	return (flag_redir);
}
