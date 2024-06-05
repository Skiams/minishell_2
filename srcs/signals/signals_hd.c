/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:37:07 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/05 22:52:15 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cc_heredoc(int sig)
{
	(void)sig;
	dprintf(2, "on est dans cc heredoc\n");
	ft_putchar(1, '\n');
	close(0);
	g_sig_exit = 2;
	ft_exit_code(130, ADD);
}

void	ft_handle_sig_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_cc_heredoc);
}
