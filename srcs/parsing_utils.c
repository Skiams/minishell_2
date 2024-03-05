/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:11:37 by ahayon            #+#    #+#             */
/*   Updated: 2024/03/05 18:02:40 by ahayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < 9 || str[i] > 13) || str[i] != 32)
			return (false);
		i++;
	}
	return (true);
}

char	*ft_del_edge_spaces(char *str)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(str) - 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while ((str[len] >= 9 && str[len] <= 13) || str[len] == 32)
			len--;
	new_str = ft_substr(str, i, len - i + 1);
	return (new_str);
}

bool	ft_is_whitespace(char *str, int i)
{
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		return (true);
	else
		return (false);
}
