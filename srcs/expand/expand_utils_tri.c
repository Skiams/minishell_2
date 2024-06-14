/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_tri.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:10:33 by ahayon            #+#    #+#             */
/*   Updated: 2024/06/14 14:26:45 by ahayon           ###   ########.fr       */
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

void	ft_classic_exp_bis(char *str, size_t *i, int code)
{
	if (code == NO_QUOTES)
	{
		while (str[*i] && str[*i] != '$' && str[*i] != '=' && str[*i] != '"'
			&& str[*i] != '/')
			(*i)++;
	}
	else if (code == QUOTES)
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
	}
}
