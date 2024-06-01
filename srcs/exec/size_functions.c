/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:15:31 by eltouma           #+#    #+#             */
/*   Updated: 2024/06/01 16:22:51 by eltouma          ###   ########.fr       */
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
		if (!ft_is_space(str[i]) && str[i] != 58)
			j += 1;
		while ((!ft_is_space(str[i]) && str[i] != 58) && str[i] != '\0')
			i += 1;
		while ((ft_is_space(str[i]) || str[i] == 58) && str[i] != '\0')
			i += 1;
	}
	return (j);
}

int	ft_count_size_of_word_colon(char *str)
{
	int	i;

	i = 0;
	while ((!ft_is_space(str[i]) && str[i] != 58) && str[i] != '\0')
		i += 1;
	return (i);
}

int	ft_count_size_of_word(char *str)
{
	int	i;

	i = 0;
	while (!ft_is_space(str[i]) && str[i] != '\0')
		i += 1;
	return (i);
}
