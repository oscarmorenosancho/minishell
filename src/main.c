/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:27:13 by edomingu          #+#    #+#             */
/*   Updated: 2023/05/26 17:55:02 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_main_exec(t_main_data *d)
{
	d->matrix = ft_split_tokens(d->line, d->ed.envl);
	if (d->matrix && !ft_check_redirs(d->matrix))
	{
		d->ed.cmd_list = ft_init_cmd_lst(d->matrix);
		ft_cmd_exe(&d->ed);
		ft_handlers_father();
	}
	else if (d->matrix)
		d->ed.result = 258;
}

static void	ft_main_loop(t_main_data *d)
{
	d->flag_quotes = ft_check_quotes(d->line);
	d->flag_pipes = ft_check_pipes(d->line);
	if (d->flag_quotes && d->flag_pipes)
		ft_main_exec(d);
	else if (!d->flag_quotes)
	{
		d->ed.result = 1;
		ft_putstr_fd(ERROR_UNCLOSED_QUOTES, 2);
	}
	else if (!d->flag_pipes)
	{
		d->ed.result = 258;
		ft_putstr_fd(ERROR_SYN_PIPE, 2);
	}
	if (d->line && *d->line)
		add_history(d->line);
	ft_dispose_cmd_lst(&d->ed.cmd_list);
	ft_free_matrix((void ***)&d->matrix);
	ft_free((void **)&d->line);
	d->line = readline(PROMPT);
}

// system("leaks minishell");
int	main(int argc, char **argv, char **envp)
{
	t_main_data	data;

	(void)argc;
	(void)argv;
	g_status = &data.ed.result;
	data.ed.cmd_list = NULL;
	data.ed.envl = ft_envl_init(envp);
	ft_handlers_father();
	data.line = readline(PROMPT);
	data.matrix = NULL;
	while (data.line != NULL)
	{
		data.ed.envl = ft_lstsort(&data.ed.envl, ft_env_comp);
		ft_main_loop(&data);
	}
	ft_free((void **)&data.line);
	ft_lstclear(&data.ed.envl, ft_dispose_env_var);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	return (data.ed.result);
}
