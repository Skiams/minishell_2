/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:42:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/05 17:05:41 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_echo_n(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
		return (true);
	else
		return (false);
}
void	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (args[i] && ft_is_echo_n(args[i]))
	{
		i++;
		n = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
}
