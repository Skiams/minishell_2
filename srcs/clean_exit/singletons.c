/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:44:24 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/09 16:13:21 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit_code(int exit_code, int mode)
{
	static int	code = 0;

	if (mode == ADD)
		code = exit_code;
	if (mode == GET)
		return (code);
	return (code);
}

int	ft_expand_code(int expand_code, int mode)
{
	static int	code = 0;

	if (mode == ADD)
		code = expand_code;
	if (mode == GET)
		return (code);
	return (code);
}
