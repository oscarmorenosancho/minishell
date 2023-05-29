/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:28:03 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/26 13:21:52 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_split_tokens(const char *str, t_list *envl)
{
	char	*tmp;
	char	**tab_str;
	int		flag_heredoc;

	tab_str = NULL;
	tmp = ft_read_word(str, envl, 0);
	while (tmp)
	{
		flag_heredoc = 0;
		if (!ft_strcmp(tmp, "<<"))
			flag_heredoc = 1;
		ft_str_matrix_add(&tab_str, tmp);
		ft_free((void **)&tmp);
		tmp = ft_read_word(str, envl, flag_heredoc);
	}
	ft_free((void **)&tmp);
	return (tab_str);
}

static const char	*ft_look_for_dollar(char **str_parsed, const char *str, \
										char *quote)
{
	while (*str && (*str != '$' || *quote == '\''))
	{
		if (*quote == *str)
			*quote = '\0';
		else if (ft_is_a_quote(*str) && !*quote)
			*quote = *str;
		ft_stradd_char(str_parsed, *str++);
	}
	return (str);
}

void	ft_added_trimmed(char **s1, char *s2)
{
	char	*last_p;
	char	*sub_s;

	if (!s2)
		return ;
	while (ft_is_whitespace(*s2))
		s2++;
	last_p = s2 + ft_strlen_safe(s2) - 1;
	while (ft_is_whitespace(*last_p))
		last_p--;
	sub_s = ft_substr(s2, 0, last_p - s2 + 1);
	ft_stradd_str(s1, sub_s);
	free(sub_s);
}

static const char	*ft_add_env_var(char **str_parsed, const char *str, \
									char quote, t_list *envl)
{
	char	tmp;

	str++;
	if (ft_isalnum(*str) || *str == '_')
	{
		if (!quote)
			tmp = '"';
		else
			tmp = quote;
		ft_stradd_char(str_parsed, tmp);
		if (quote)
			ft_stradd_str(str_parsed, ft_get_envl(str, envl));
		else
			ft_added_trimmed(str_parsed, ft_get_envl(str, envl));
		ft_stradd_char(str_parsed, tmp);
		while (ft_isalnum(*str) || *str == '_')
			str++;
	}
	else if (!ft_is_a_quote(*str) || quote)
		ft_stradd_char(str_parsed, '$');
	return (str);
}

char	*ft_expand_env_vars(const char *str, t_list *envl)
{
	char	*str_parsed;
	char	quote;

	quote = '\0';
	str_parsed = NULL;
	while (str && *str)
	{
		str = ft_look_for_dollar(&str_parsed, str, &quote);
		if (*str == '$')
			str = ft_add_env_var(&str_parsed, str, quote, envl);
		else if (*str)
			ft_stradd_char(&str_parsed, *str++);
	}
	return (str_parsed);
}
