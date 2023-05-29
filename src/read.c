/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:43:34 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/26 13:35:31 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_read_quotes(const char *str, int *pos)
{
	char	*word;
	char	quote;

	word = ft_calloc(1, sizeof(char));
	quote = str[*pos];
	if (str[*pos] == quote)
		ft_stradd_char(&word, str[(*pos)++]);
	while (str[*pos] && str[*pos] != quote)
		ft_stradd_char(&word, str[(*pos)++]);
	if (str[*pos] == quote)
		ft_stradd_char(&word, str[(*pos)++]);
	return (word);
}

char	*ft_read_word_no_quotes(const char *str, int *pos)
{
	char	*word;

	word = NULL;
	while (str && !ft_is_end_of_word(str[*pos]) && !ft_is_a_quote(str[*pos]))
	{
		ft_stradd_char(&word, str[*pos]);
		(*pos)++;
	}
	return (word);
}

char	*ft_read_word_redir(const char *str, int *pos)
{
	char	*word;
	char	redir;

	if (!str || !*str)
		return (NULL);
	word = (char *)ft_calloc(1, sizeof(char));
	if (word == NULL)
		return (NULL);
	redir = str[*pos];
	ft_stradd_char(&word, redir);
	(*pos)++;
	if (redir == '|' || str[*pos] != redir)
		return (word);
	ft_stradd_char(&word, redir);
	(*pos)++;
	return (word);
}

static void	ft_read_word_loop(const char *str, char **word, char *tmp, int *pos)
{
	if (ft_is_a_quote(str[*pos]))
		ft_stradd_str(word, tmp = ft_read_quotes(str, pos));
	else
		ft_stradd_str(word, tmp = ft_read_word_no_quotes(str, pos));
	free(tmp);
}

char	*ft_read_word(const char *str, t_list *envl, int flag_heredoc)
{
	static int	pos = 0;
	char		*word;
	char		*tmp;

	if (!str || !*str)
		return (NULL);
	while (ft_is_whitespace(str[pos]))
		pos++;
	if (str[pos] == '\0')
		return ((char *)(long int)(pos = 0));
	if (str[pos] == '|' || str[pos] == '<' || str[pos] == '>')
		return (ft_read_word_redir(str, &pos));
	tmp = NULL;
	word = NULL;
	while (str[pos] && !ft_is_end_of_word(str[pos]))
		ft_read_word_loop(str, &word, tmp, &pos);
	if (!flag_heredoc)
		tmp = ft_expand_env_vars(word, envl);
	else if (word)
		tmp = ft_strdup(word);
	free(word);
	return (tmp);
}
