/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:10:40 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/15 17:11:44 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_end_quotes(char *str, int i, char c)
{
	i++;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
	{
		i++;
		return (i);
	}
	else
		return (0);
}
