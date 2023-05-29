/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:57:39 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/12 13:14:18 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_remove_quotation_marks(char *arg)
{
	char	*new_arg;
	char	quote;
	char	*p_new_arg;

	if (!arg)
		return (NULL);
	new_arg = ft_calloc(ft_strlen_safe(arg) + 1, sizeof(char));
	if (!new_arg)
		return (NULL);
	p_new_arg = new_arg;
	quote = '\0';
	while (*arg)
	{
		if (ft_is_a_quote(*arg) && quote == '\0')
			quote = *arg;
		else if (ft_is_a_quote(*arg) && quote == *arg)
			quote = '\0';
		else
			*(p_new_arg++) = *arg;
		arg++;
	}
	return (new_arg);
}

void	ft_read_quotes_loop(const char *str, int *pos, char **word)
{
	char	quote;

	quote = str[*pos];
	ft_stradd_char(word, str[*pos]);
	(*pos)++;
	while (str[*pos] && str[*pos] != quote)
	{
		ft_stradd_char(word, str[*pos]);
		(*pos)++;
	}
	if (str[*pos] == quote)
	{
		ft_stradd_char(word, str[*pos]);
		(*pos)++;
	}
}
