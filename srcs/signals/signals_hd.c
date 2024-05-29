/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:37:07 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/29 17:22:20 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cc_heredoc(int sig)
{
	(void)sig;
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
