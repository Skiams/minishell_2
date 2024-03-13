/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:10:40 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/13 13:15:13 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_end_quotes(char *str, int i)
{
	while (str[i] && str[i] != '\'' && str[i] != '"')
		i++;
	if (str[i] == '\'' || str[i] == '"')
	{
		i++;
		return (i);
	}
	else
		return (0);
}

bool	ft_check_quotes(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' && str[i] == '"')
			return (true);
		i++;
	}
	return (false);
}