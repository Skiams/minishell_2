/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:18:10 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/13 18:53:36 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error_handle(int err_code, char *str, int fd)
{
	(void)fd;
	if (err_code == 1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token", 1);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	ft_error_quotes()
{
	ft_putstr_fd("minishell: Syntax error: Unterminated quoted string\n");
}
