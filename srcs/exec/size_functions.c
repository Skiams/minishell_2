/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:15:31 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/28 15:12:21 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_words(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32 && str[i] != 58)
			j += 1;
		while (!(str[i] >= 9 && str[i] <= 13)
			&& str[i] != 32 && str[i] != 58 && str[i] != '\0')
			i += 1;
		while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 58)
			&& str[i] != '\0')
			i += 1;
	}
	return (j);
}

int	ft_count_size_of_word(char *str)
{
	int	i;

	i = 0;
	while (!(str[i] >= 9 && str[i] <= 13)
		&& str[i] != 32 && str[i] != 58 && str[i] != '\0')
		i += 1;
	return (i);
}
