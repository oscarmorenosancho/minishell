/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:42:52 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/26 13:05:21 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef struct s_uic_data{
	char	*line;
	char	*tmp;
	int		is_end;
	int		aux_fds[2];
}	t_uic_data;

static void	ft_user_input_core(t_built_ins_funct_args *bifa, char *end, int fd, \
								t_list *envl)
{
	t_uic_data	d;

	ft_dups(d.aux_fds);
	ft_dups2(bifa->tmp_stfds);
	d.line = readline(SUBPROMPT);
	d.tmp = NULL;
	d.is_end = 0;
	while (! d.is_end && d.line)
	{
		d.is_end = ft_strcmp(d.line, end) == 0;
		if (! d.is_end)
		{
			d.tmp = ft_expand_env_vars_heredoc(d.line, envl);
			if (d.tmp)
				ft_putstr_fd(d.tmp, fd);
			ft_putchar_fd('\n', fd);
			ft_free((void **)&d.tmp);
		}
		ft_free((void **)&d.line);
		if (! d.is_end)
			d.line = readline(SUBPROMPT);
	}
	ft_free((void **)&d.line);
	ft_free((void **)&d.tmp);
	ft_dups2(d.aux_fds);
}

static void	ft_ui_f(t_built_ins_funct_args *bifa, pid_t fr, int *st, int *fds)
{
	ft_close(&fds[1]);
	waitpid(fr, st, 0);
	if (WIFSIGNALED(*st))
	{
		ft_putstr_repl_line_n_redisp("\n", "");
		bifa->ed->result = 1;
		bifa->abort = 1;
	}
}

static void	ft_ui_s(t_built_ins_funct_args *bifa, int *fds, char *end, \
					t_list *envl)
{
	signal(SIGINT, SIG_DFL);
	ft_close(&fds[0]);
	ft_user_input_core(bifa, end, fds[1], envl);
	ft_close(&fds[1]);
	exit(0);
}

int	ft_user_input(t_built_ins_funct_args *bifa, char *end)
{
	int		fds[2];
	pid_t	fork_ret;
	int		status;
	char	*aux_end;

	if (!end || !*end)
	{
		ft_putstr_fd(ERROR_SYN_NL, 2);
		bifa->ed->result = 258;
		bifa->abort = 1;
		return (-1);
	}
	aux_end = ft_remove_quotation_marks(end);
	pipe(fds);
	ft_handler_ignore();
	fork_ret = fork();
	if (fork_ret == 0)
		ft_ui_s(bifa, fds, aux_end, bifa->ed->envl);
	else if (fork_ret > 0)
		ft_ui_f(bifa, fork_ret, &status, fds);
	free(aux_end);
	return (fds[0]);
}
