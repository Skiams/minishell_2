/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_tri.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:10:33 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/13 19:25:53 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_remove_space(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	if (str[0] != '\0')
	{
		while (str[j])
			j++;
		while (str[j - 1] && (str[j - 1] == 32 || str[j - 1] == 9))
			j--;
		while (str[i] && (str[i] == 32 || str[i] == 9))
			i++;
		res = malloc(sizeof(char) * (j - i) + 1);
		if (!res)
			return (NULL);
		while (i < j)
			res[k++] = str[i++];
		res[k] = '\0';
		return (ft_free_ptr(str), res);
	}
	return (str);
}
