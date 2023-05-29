/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:47:47 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/26 16:44:01 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_a_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	ft_check_quotes(const char *str)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (!quote && ft_is_a_quote(str[i]))
			quote = str[i];
		else if (quote == str[i])
			quote = 0;
		i++;
	}
	return (!quote);
}

static int	ft_check_pipes_loop(int i, int *closed, char *quote, \
								const char *str)
{
	if (str[i] == '|' && !*quote)
	{
		if (!*closed)
			return (0);
		*closed = 0;
	}
	else if (!ft_is_whitespace(str[i]))
	{
		*closed = 1;
		if (*quote == str[i])
			*quote = '\0';
		else if (ft_is_a_quote(str[i]))
			*quote = str[i];
	}
	return (1);
}

int	ft_check_pipes(const char *str)
{
	int		i;
	int		closed;
	char	quote;

	if (!str)
		return (1);
	closed = 1;
	i = 0;
	while (ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '|')
		return (0);
	quote = '\0';
	while (str[i])
	{
		if (!ft_check_pipes_loop(i, &closed, &quote, str))
			return (0);
		i++;
	}
	return (closed);
}
