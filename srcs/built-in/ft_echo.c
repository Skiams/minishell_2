/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:42:22 by ahayon            #+#    #+#             */
/*   Updated: 2024/05/09 18:34:39 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_is_echo_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	else
		return (false);
}

void	ft_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (!*args)
		return ;
	while (args[i] && ft_is_echo_n(args[i]))
	{
		i++;
		n = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && ft_strcmp(args[i], "\0") != 0)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', 1);
}
