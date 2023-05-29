/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_increase_shlvl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:43:46 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/19 17:30:52 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_list	*ft_print_shlvl_warn_n_resetl(t_list **envl, int shlvl)
{
	ft_putstr_fd(MSG_SHLVL_INI, 1);
	ft_putnbr_fd(shlvl, 1);
	ft_putstr_fd(MSG_SHLVL_END, 1);
	return (ft_set_envl("SHLVL", "1", envl));
}

t_list	*ft_increase_shlvl_envl(t_list **envl)
{
	char	*shlvl;
	int		lvl;

	shlvl = ft_get_envl("SHLVL", *envl);
	if (!shlvl || !ft_isnumeric(shlvl))
		return (ft_set_envl("SHLVL", "1", envl));
	lvl = ft_atoi(shlvl) + 1;
	if (lvl < 0)
		return (ft_set_envl("SHLVL", "0", envl));
	if (lvl > 1000)
		return (ft_print_shlvl_warn_n_resetl(envl, lvl));
	if (lvl == 1000)
		return (ft_set_envl("SHLVL", "", envl));
	shlvl = ft_itoa(lvl);
	ft_set_envl("SHLVL", shlvl, envl);
	free(shlvl);
	return (*envl);
}
