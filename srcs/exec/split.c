/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayon <ahayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:27 by eltouma           #+#    #+#             */
/*   Updated: 2024/05/31 18:59:20 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*ft_fill_tab_colon(char *str)
{
	int		i;
	int		size;
	char	*s;

	i = 0;
	if (!str)
		return (NULL);
	size = ft_count_size_of_word_colon(str);
	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		return (NULL);
	while (str[i] != '\0' && str[i] != 58 && !ft_is_space(str[i]))
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_fill_tab(char *str)
{
	int		i;
	int		size;
	char	*s;

	i = 0;
	if (!str)
		return (NULL);
	size = ft_count_size_of_word(str);
	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		return (NULL);
	while (str[i] != '\0' && !ft_is_space(str[i]))
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

char	**ft_return_tab(char *str)
{
	char	**tab;

	if (!str)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_count_words(str) + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_split_exec(char *str)
{
	int		j;
	char	**tab;

	j = 0;
	if (!str)
		return (NULL);
	tab = ft_return_tab(str);
	if (!tab)
		return (NULL);
	tab[ft_count_words(str)] = NULL;
	while (*str != '\0')
	{
		if (!ft_is_space(*str) && *str != 58)
		{
			tab[j] = ft_fill_tab_colon(str);
			if (!tab[j++])
				return (ft_free_tab(tab));
			while (*str != '\0' && *str != 58 && !(ft_is_space(*str)))
				str += 1;
		}
		else
			str += 1;
	}
	return (tab);
}
