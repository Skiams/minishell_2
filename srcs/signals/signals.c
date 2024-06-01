/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:41:43 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/01 16:38:44 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cc_handler(int sig)
{
	(void)sig;
	ft_putchar(1, '\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_exit = 2;
	ft_exit_code(130, ADD);
}

void	ft_cc_blocking(int sig)
{
	(void)sig;
	ft_putchar(1, '\n');
	g_sig_exit = 2;
	ft_exit_code(130, ADD);
}

void	ft_bckslsh_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	ft_exit_code(131, ADD);
}

void	ft_handle_signal(int code)
{
	if (code == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ft_cc_handler);
	}
	if (code == 2)
	{
		signal(SIGQUIT, &ft_bckslsh_handler);
		signal(SIGINT, &ft_cc_blocking);
	}
}
