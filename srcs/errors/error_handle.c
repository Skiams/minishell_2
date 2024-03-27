/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:18:10 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/27 17:56:52 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
}

void	ft_error_quotes(void)
{
	ft_putstr_fd("minishell: Syntax error: Unterminated quoted string\n", 2);
}
