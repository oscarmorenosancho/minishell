/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:27:42 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/26 13:28:01 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_read_command(char **cmd_line)
{
	static int	pos = 0;
	char		**cmd;

	if (!cmd_line || !*cmd_line)
		return (NULL);
	if (cmd_line[pos] == NULL)
	{
		pos = 0;
		return (NULL);
	}
	cmd = NULL;
	while (cmd_line[pos] && ft_strcmp(cmd_line[pos], "|") != 0)
	{
		ft_str_matrix_add(&cmd, cmd_line[pos]);
		pos++;
	}
	if (cmd_line[pos])
		pos++;
	return (cmd);
}
