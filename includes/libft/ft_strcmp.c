/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skiam <skiam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:19:09 by skiam             #+#    #+#             */
/*   Updated: 2024/04/05 19:30:01 by skiam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	int	i;

// 	i = 0;
// 	if (s1[i] && s2[i])
// 	{
// 		while (s1[i] && s2[i])
// 		{
// 			if (s1[i] - s2[i])
// 				return (s1[i] - s2[i]);
// 			++i;
// 		}
// 		return (s1[i] - s2[i]);
// 	}
// 	return (s1[i] - s2[i]);
// }

int	ft_strcmp(const char *argv, const char *str)
{
	int	i;

	i = 0;
	if (!argv || !str)
		return (1);
	while (str[i] != '\0' && argv[i] != '\0' && argv[i] == str[i])
		i += 1;
	return (argv[i] - str[i]);
}