/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:41:43 by ahayon            #+#    #+#             */
/*   Updated: 2024/04/12 15:27:02 by ahayon           ###   ########.fr       */
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

void	ft_handle_signal()
{
	signal(SIGINT, &ft_cc_handler);
}
