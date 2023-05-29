/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:20:37 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/09 18:50:57 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_expand_stat_loop(int *flag, char **tmp, char **res, char *status)
{
	if (!*flag && !ft_strncmp(*tmp, "$?", 2))
	{
		ft_stradd_str(res, status);
		(*tmp)++;
	}
	else
	{
		if (**tmp == '\'')
			*flag = !*flag;
		ft_stradd_char(res, **tmp);
	}
	(*tmp)++;
}

void	ft_expand_status(char **cmd)
{
	char	*res;
	char	*tmp;
	int		flag_simple_quote;
	char	*str_status;

	str_status = ft_itoa(*g_status);
	flag_simple_quote = 0;
	while (cmd && *cmd)
	{
		tmp = *cmd;
		res = NULL;
		while (tmp && *tmp)
			ft_expand_stat_loop(&flag_simple_quote, &tmp, &res, str_status);
		ft_free((void **)cmd);
		*cmd = res;
		cmd++;
	}
	free(str_status);
}
