/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:18:10 by ahayon            #+#    #+#             */
/*   Updated: 2024/02/29 19:09:02 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error_handle(int err_code, char *str, int fd)
{
	(void)fd;
	if (err_code == 1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token", 1);
		ft_putstr_fd(str, 1);
	}
}
