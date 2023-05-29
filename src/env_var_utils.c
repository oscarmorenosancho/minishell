/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:18:24 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/19 12:24:16 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_format_env_var_line(unsigned int i, void *c, void *arg)
{
	t_env_var	*content;
	char		**env_t;

	if (!c || !arg)
		return ;
	env_t = arg;
	content = c;
	env_t[i] = NULL;
	ft_stradd_str(&env_t[i], content->name);
	if (content->value)
	{
		ft_stradd_char(&env_t[i], '=');
		ft_stradd_str(&env_t[i], content->value);
	}
}

void	ft_print_env_var_line(unsigned int i, void *c, void *arg)
{
	t_env_var	*content;
	int			fd;

	(void)i;
	if (!c)
		return ;
	content = c;
	fd = (int)arg;
	if (content->name && content->value)
	{
		ft_putstr_fd(content->name, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(content->value, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_print_exp_var_line(unsigned int i, void *c, void *arg)
{
	t_env_var	*content;
	int			fd;

	(void)i;
	if (!c)
		return ;
	content = c;
	fd = (int)arg;
	if (content->name)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(content->name, fd);
		if (content->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(content->value, fd);
			ft_putchar_fd('"', fd);
		}
		ft_putchar_fd('\n', fd);
	}
}
