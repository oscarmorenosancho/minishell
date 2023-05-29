/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:34:41 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/22 12:28:44 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_sigint_handler_father(int sig)
{
	(void)sig;
	*g_status = 1;
	ft_putchar_fd('\n', 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// set termios_save.c_lflag |= ECHOCTL;
// reset termios_save.c_lflag &= ~ECHOCTL;
// rl_catch_signals = 0;
void	ft_handlers_father(void)
{
	struct termios	termios_save;

	tcgetattr(0, &termios_save);
	termios_save.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_save);
	signal(SIGINT, ft_sigint_handler_father);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handler_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handlers_son(void)
{
	struct termios	termios_save;

	tcgetattr(0, &termios_save);
	termios_save.c_lflag |= ECHOCTL;
	tcsetattr(0, 0, &termios_save);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_handlers_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
