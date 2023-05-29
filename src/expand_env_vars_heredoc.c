/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:41:08 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/19 17:23:04 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static const char	*ft_add_env_var_heredoc(char **str_parsed, \
											const char *name, \
											char quote, t_list *envl)
{
	name++;
	if (ft_isalnum(*name) || *name == '_')
	{
		ft_stradd_str(str_parsed, ft_get_envl(name, envl));
		while (ft_isalnum(*name) || *name == '_')
			name++;
	}
	else if (!ft_is_a_quote(*name) || *name == quote)
		ft_stradd_char(str_parsed, '$');
	return (name);
}

char	*ft_expand_env_vars_heredoc(const char *str, t_list *envl)
{
	char	*str_parsed;
	char	quote;

	quote = '\0';
	str_parsed = NULL;
	while (str && *str)
	{
		if (*str == '$')
			str = ft_add_env_var_heredoc(&str_parsed, str, quote, envl);
		else if (*str)
			ft_stradd_char(&str_parsed, *str++);
	}
	return (str_parsed);
}
