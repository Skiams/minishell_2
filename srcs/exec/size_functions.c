/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:15:31 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/11 17:48:38 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i += 1;
	return (i);
}

int	ft_count_words(char *str)
{
	int	i;
	int	j;

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
